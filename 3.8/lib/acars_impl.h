/* -*- c++ -*- */
/*
 * Copyright 2020 gr-acars author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_ACARS_ACARS_IMPL_H
#define INCLUDED_ACARS_ACARS_IMPL_H

#include <acars/acars.h>
#include <fftw3.h>

namespace gr {
  namespace acars {

    class acars_impl : public acars
    {
     private:
        int _pos;
        int _Ntot;
        int _total;
        int _acq;
        int _filenum;
        float *_d;
        float c2400[20], c1200[20];
        float s2400[20], s1200[20];
        float _seuil;
        char *_filename;
        FILE *_FICHIER;
        fftw_complex *_c2400x13,*_fc2400x13,*_fd,*_s,*_ss;
        float *_rs12,*_rs24,*_rc12,*_rc24,*_out;
        float *_dm;
        char *_toutd,*_tout,*_message;
        void acars_decodeur (float seuil1,char *filename);
        void acars_parse (char *message,int ends,FILE *filename);
        void remove_avgf(float *d,float *out,int tot_len,const float fil_len);
        void acars_dec(float *d,int N,float seuil,float *c2400,float *s2400,float *c1200,float *s1200,FILE *file);

     public:
      void set_seuil(float);
      acars_impl(float seuil, char* filename);
      ~acars_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace acars
} // namespace gr

#endif /* INCLUDED_ACARS_ACARS_IMPL_H */

