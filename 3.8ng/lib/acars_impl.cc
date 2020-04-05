/* -*- c++ -*- */
/*
 * Copyright 2020 gr-acars author.
 */

#undef jmfdebug

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "acars_impl.h"
#include<time.h>

#define fe        48000   // sampling frequency
#define CHUNK_SIZE 1024
#define MESSAGE   (220*2) // twice the max message size !
#define MAXSIZE   (MESSAGE*8*fe) // 48000/2400=20 symbol/bit & 8 bits*260 char=41600
#define dN  5

namespace gr {
  namespace acars {

    acars::sptr
    acars::make(float seuil, std::string filename)
    {
      return gnuradio::get_initial_sptr
        (new acars_impl(seuil, filename));
    }

    /*
     * The private constructor
     */
    acars_impl::acars_impl(float seuil1, std::string filename)
      : gr::sync_block("acars",
              gr::io_signature::make(1, 1, sizeof(float)), // max 4 inputs
              gr::io_signature::make(0, 0, 0))
              , _seuil(seuil1)
{
  int t;
  char cfilename[filename.size()+1];
  filename.copy(cfilename,filename.size()+1);cfilename[filename.size()]=0;
  _Ntot=0;
  _N=0;
  _threshold=0.;
  _FILE=fopen(cfilename,"a");  // faster than allocating big arrays for
  _decompte=0;  
  set_seuil(seuil1);             // each new sentence processed
  _d=(float*)malloc(MAXSIZE*sizeof(float));
  _tout=(char*)malloc(MESSAGE*8);  // bits
  _toutd=(char*)malloc(MESSAGE*8);  // bits
  _message=(char*)malloc(MESSAGE); // bytes
  _somme=(char*)malloc(MESSAGE); // bytes
  printf("threshold value=%f, filename=%s\n",seuil1,cfilename);
  set_output_multiple(CHUNK_SIZE); // only trigger processing if that amount of samples was accumulated
}

void acars_impl::set_seuil(float seuil1)
{printf("new threshold: %f\n",seuil1);fflush(stdout);
 _seuil=seuil1;
}

int acars_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
 {
  int k,i,t,n,pos_start,pos_end;
  float std;
  float* data;
  const float* in = (const float *) input_items[0];

 _N=noutput_items;
 data=(float*)malloc(_N*sizeof(float));
 if (_threshold==0.)
    {_threshold=remove_avgf(in,data,_N);std=_threshold;}    // d=d-mean(m); -> returns std()
 else std=remove_avgf(in,data,_N);        // d=d-mean(m); -> returns std()

 if ((std>(_seuil*_threshold))||(_decompte>0))   // ACARS sentence detected: accumulate
    {// printf("%d\tdetected %f\n",_N,std*1000.);
     for (k=0;k<_N;k++) _d[_Ntot+k]=in[k]; // _Ntot: current position
     _Ntot+=_N;
     _decompte++;if (_decompte==3) _decompte=0;
    }
 else                                    // NO ACARS detected => decode if we had some data
    {_threshold=std;                      // update threshold
     // printf("%d\t no %f\n",_N,std*1000.);
     if (_Ntot>0)                         // we had some data => process
       {printf("threshold: %f processing length: %d ",_threshold,_Ntot);
        remove_avgf(_d,_d,_Ntot);
        pos_start=0;
        while ((_d[pos_start]<(_seuil*_threshold))&&(pos_start<_Ntot)) pos_start++; // get beginning
        printf("start: %d, ",pos_start);fflush(stdout);
        pos_end=_Ntot-1;
        while (_d[pos_end]<(_seuil*_threshold)) pos_end--;     // get end
        printf("end: %d\n",pos_end);fflush(stdout);
        if (pos_end>pos_start) 
           {
            acars_dec(&_d[pos_start], pos_end-pos_start);
           }
           else printf("Error: pos_end<pos_start\n");
        _Ntot=0;                         // finished processing: clear buffer
       }
    }
  // Tell runtime system how many input items we consumed on
  // each input stream.
 free(data);
 consume_each (_N); 
 return 0; // noutput_items;
}

    // Our virtual destructor.
acars_impl::~acars_impl ()
{free(_tout);
 free(_toutd);
 free(_message);
 free(_somme);
}

// http://www.scancat.com/Code-30_html_Source/acars.html
void acars_impl::acars_parse(char *message,int ends)
{int k;
 if (ends>12)
    if ((message[0]==0x2b) && (message[1]==0x2a) && // sync
        (message[2]==0x16) && (message[3]==0x16) && // sync
        (message[4]==0x01))                         // Start Of Heading SOH
        {printf("\nAircraft="); fprintf(_FILE ,"\nAircraft=");
         for (k=6;k<13;k++) {printf("%c",message[k]); fprintf(_FILE ,"%c",message[k]);}
         printf("\n");fprintf(_FILE,"\n");
         if (ends>17) 
            {if (message[17]==0x02) {printf("STX\n"); fprintf(_FILE, "STX\n");}
             if (ends>=21) 
                {printf("Seq. No="); fprintf(_FILE, "Seq. No=");
                 for (k=18;k<22;k++) {printf("%02x ",message[k]); fprintf(_FILE, "%02x ",message[k]);}
                 for (k=18;k<22;k++) 
                     if ((message[k]>=32) || (message[k]==0x10) || (message[k]==0x13))
                        {printf("%c",message[k]); fprintf(_FILE, "%c",message[k]);
                        }
                 printf("\n"); fprintf(_FILE, "\n");
                 if (ends>=27) 
                    {printf("Flight="); fprintf(_FILE, "Flight=");
                     for (k=22;k<28;k++) {printf("%c",message[k]); fprintf(_FILE, "%c",message[k]);}
                     printf("\n"); fprintf(_FILE, "\n");
                     if (ends>=28) 
                        {k=28;
                         do {if (message[k]==0x03) {printf("ETX"); fprintf(_FILE, "ETX"); }
                                else if ((message[k]>=32) || (message[k]==0x10) || (message[k]==0x13))
                                     {printf("%c",message[k]); fprintf(_FILE, "%c",message[k]);
                                     }
                             k++;
                            } while ((k<ends-1) && (message[k-1]!=0x03));
                         printf("\n"); fprintf(_FILE, "\n");
                        }
                    }
                }
            }
        }
 fflush(stdout);fflush(_FILE);
}

float acars_impl::remove_avgf(const float *d,float *out,int tot_len)
{int k;
 float avg=0.,std=0.;
 for (k=0;k<tot_len;k++) avg+=d[k];
 avg/=(float)tot_len;
 for (k=0;k<tot_len;k++)
     {out[k]=(d[k]-avg);
      std+=out[k]*out[k]; // variance
     }
 return(sqrt(std/(float)tot_len)); // return standard deviation=sqrt(var)
}

void acars_impl::acars_dec(float *d,int N)
{
 int fin,k,kcut,i,f,t,n,l,pos2400;
 char s[256];
 float a=0.,max24=0.,seuildyn,max2400;
 char c;
// int b=0,go=0;
 time_t tm;
 FILE *fil;
 gr_complex mul;
 gr_complex *tmp, *_c1200, *_c2400, *_signal, *_fc1200, *_fc2400, *_fsignal, *_ffc1200, *_ffc2400;
 fft::fft_complex* plan_1200 = new fft::fft_complex(N, true);
 fft::fft_complex* plan_2400 = new fft::fft_complex(N, true);
 fft::fft_complex* plan_sign = new fft::fft_complex(N, true);
 fft::fft_complex* plan_R1200= new fft::fft_complex(N, false);
 fft::fft_complex* plan_R2400= new fft::fft_complex(N, false);

 _c2400=plan_2400->get_inbuf();
 for (t=0;t<40;t++)                          //  convolution with *2* periods
     _c2400[t]=gr_complex{(float)cos((float)t*2400./fe*2*M_PI),(float)sin((float)t*2400./fe*2*M_PI)}; 
 for (t=40;t<N;t++)     // zero padding
     _c2400[t]=gr_complex{0.,0.}; 

 _c1200=plan_1200->get_inbuf();
 for (t=0;t<40;t++)                          //  convolution with *2* periods
     _c1200[t]=gr_complex{(float)cos((float)t*1200./fe*2*M_PI),(float)sin((float)t*1200./fe*2*M_PI)}; 
 for (t=40;t<N;t++)     // zero padding
     _c1200[t]=gr_complex{0.,0.}; 
 
 _signal=plan_sign->get_inbuf();
 for (t=0;t<N;t++)     // zero padding
     _signal[t]=gr_complex{d[t],0.};
 time(&tm);
 sprintf(s,"%s",ctime(&tm));
 printf("\n%s",s);
#ifdef jmfdebug
 printf("len=%d\n",N);
#endif

 plan_2400->execute();
 plan_1200->execute();
 plan_sign->execute();
 _fc2400=plan_2400->get_outbuf();
 _fc1200=plan_1200->get_outbuf();
 _fsignal=plan_sign->get_outbuf();
 _ffc1200=plan_R1200->get_inbuf();
 _ffc2400=plan_R2400->get_inbuf();
 for (k=0;k<N;k++) 
    {mul=_fc2400[k]*_fsignal[k];
          //_fc2400[k].real()*_fsignal[k].real()-_fc2400[k].imag()*_fsignal[k].imag(), \
          //_fc2400[k].imag()*_fsignal[k].real()+_fc2400[k].real()*_fsignal[k].imag() };
     _ffc2400[k]=mul/(float)N;
     mul=_fc1200[k]*_fsignal[k];
          //_fc1200[k].real()*_fsignal[k].real()-_fc1200[k].imag()*_fsignal[k].imag(), \
          //_fc1200[k].imag()*_fsignal[k].real()+_fc1200[k].real()*_fsignal[k].imag()};
     _ffc1200[k]=mul/(float)N;
    }
 // Low pass filter after convolution
 kcut=(int)((float)N*3500./(float)fe); // cutoff @ 3500 Hz : df=fs/length(sf);fcut=floor(3500/df);
 for (k=kcut;k<N-kcut;k++)   // low pass filter in Matlab FFT convention
     {_ffc2400[k]={0.,0.};      // sf2400f(fcut:end-fcut)=0; 
      _ffc1200[k]={0.,0.};    // sf1200f(fcut:end-fcut)=0; 
     }
 plan_R1200 -> execute();  // result in _c1200
 plan_R2400 -> execute();  // result in _c2400
 delete plan_1200;
 delete plan_2400;
 delete plan_sign;
 _c1200=plan_R1200->get_outbuf();
 _c2400=plan_R2400->get_outbuf();
 // printf("writing file\n");
 // fil=fopen("/tmp/out","w+");
 // for (t=0;t<N;t++) 
 //     fprintf(fil,"%f %f %f %f %f\n",d[t],_c1200[t].real(),_c1200[t].imag(),_c2400[t].real(),_c2400[t].imag());
 // fclose(fil);

 // skip first 200 samples
 for (k=200;k<N;k++) _c1200[k]=gr_complex{abs(_c1200[k]),0.}; 
 // gr_complex{_c1200[k].real()*_c1200[k].real()+_c1200[k].imag()*_c1200[k].imag(),0.};  // |*|^2
 max2400=0.;
 for (k=200;k<N;k++) {_c2400[k]=gr_complex{abs(_c2400[k]),0.}; 
 // gr_complex{_c2400[k].real()*_c2400[k].real()+_c2400[k].imag()*_c2400[k].imag(),0.}; // |*|^2
                      if (_c2400[k].real()>max2400) max2400=_c2400[k].real();
                     }
 k=200;
 do {k++;} while (_c2400[k].real()>0.5*max2400);  // header as long as 2400 is strong
 printf("max2400=%f -> k=%d\n",max2400,k);
// k at the beginning of the frame
 k+=10; // move to the center of the first bit

 _toutd[0]=0;
 n=1;
 // now clock recovery ...
 while (k<N-40)
   {k+=20;
    if (_c2400[k].real()>_c1200[k].real()) _toutd[n]=1; else _toutd[n]=0;
    n++;
    if ((_c2400[k].real()>_c1200[k].real()) && ((_c1200[k+20].real()>_c2400[k+20].real())) && (_c1200[k-20].real()>_c2400[k-20].real()))
       {max2400=_c2400[k-dN].real();pos2400=-dN;
        for (l=-dN+1;l<=dN;l++)
            {// printf("\tk:%d l:%d 2400:%f 1200:%f max2400:%f\n",k,l,_c2400[k+l].real(),_c1200[k+l].real(),max2400);
             if (_c2400[k+l].real()>max2400)  // [m,p]=max(s2400(pos-3:pos+3));
                {max2400=_c2400[k+l].real();pos2400=l;} 
            } 
        // if (pos2400!=0) printf("%d: correct2400 %d\n",k,pos2400);
        k+=pos2400;
       }
    if ((_c1200[k].real()>_c2400[k].real()) && ((_c2400[k+20].real()>_c1200[k+20].real())) && (_c2400[k-20].real()>_c1200[k-20].real()))
       {max2400=_c1200[k-dN].real();pos2400=-dN;
        for (l=-dN+1;l<=dN;l++)
            {// printf("\t2400:%f 1200:%f max2400:%f\n",_c2400[k+l].real(),_c1200[k+l].real(),max2400);
             if (_c1200[k+l].real()>max2400)  // [m,p]=max(s1200(pos-3:pos+3));
                {max2400=_c1200[k+l].real();pos2400=l;} 
            } 
        // if (pos2400!=0) printf("%d: correct1200: %d\n",k,pos2400);
        k+=pos2400;
       }
   }
 delete plan_R1200;
 delete plan_R2400;
 l=0;fin=n;
 _tout[l]=1;l++;  // les deux premiers 1 sontoublies car on se sync sur 1200
 _tout[l]=1;l++;
 for (k=0;k<fin;k++)
    {if (_toutd[k]==0) _tout[l]=1-_tout[l-1]; else _tout[l]=_tout[l-1];
     l++;
    }
   n=0;
   for (k=0;k<fin;k+=8) 
       {_message[n]=_tout[k]+_tout[k+1]*2+_tout[k+2]*4+_tout[k+3]*8+_tout[k+4]*16+_tout[k+5]*32+_tout[k+6]*64;
        _somme[n]=1-(_tout[k]+_tout[k+1]+_tout[k+2]+_tout[k+3]+_tout[k+4]+_tout[k+5]+_tout[k+6]+_tout[k+7])&0x01;
        n++;
       }
   fin=n; // length of message (should be tout/8)
   n=0;
// for (k=0;k<fin;k++) {if (_message[k]==0x2b) n=k;break;} // search for the 1st 0x2b (start of message)
   // for (k=0;k<fin;k++) {printf("%02x ",_message[k]);// fprintf(file,"%02x ",_message[k]);}
   for (k=0;k<10;k++) {printf("%02x ",_message[k]); fprintf(_FILE,"%02x ",_message[k]);}
   printf("\n");
   for (k=0;k<10;k++) {printf("%02x ",_somme[k]);fprintf(_FILE,"%02x ",_message[k]);}
   printf("\n");
   for (k=n;k<fin;k++)
       if ((_message[k]>=32) || (_message[k]==13) || (_message[k]==10)) 
           {printf("%c",_message[k]);}
   printf("\n"); fprintf(_FILE,"\n"); fflush(stdout);
   acars_parse(&_message[n],fin-n);
}
//^^^^^^^^^^^^^^^^^^^^^
  } /* namespace acars */
} /* namespace gr */
