#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.4.0

from gnuradio import analog
from gnuradio import filter
from gnuradio.filter import firdes
from gnuradio import gr
from gnuradio.fft import window
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
import acars
import osmosdr
import time




class example(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 48000*24
        self.N = N = 8
        self.taps = taps = firdes.low_pass(1.0, samp_rate, samp_rate/N/2,samp_rate/N/2, window.WIN_HAMMING, 6.76)

        ##################################################
        # Blocks
        ##################################################
        self.osmosdr_source_0 = osmosdr.source(
            args="numchan=" + str(1) + " " + ""
        )
        self.osmosdr_source_0.set_time_unknown_pps(osmosdr.time_spec_t())
        self.osmosdr_source_0.set_sample_rate(samp_rate)
        self.osmosdr_source_0.set_center_freq(131.725e6, 0)
        self.osmosdr_source_0.set_freq_corr(0, 0)
        self.osmosdr_source_0.set_dc_offset_mode(0, 0)
        self.osmosdr_source_0.set_iq_balance_mode(0, 0)
        self.osmosdr_source_0.set_gain_mode(False, 0)
        self.osmosdr_source_0.set_gain(40, 0)
        self.osmosdr_source_0.set_if_gain(20, 0)
        self.osmosdr_source_0.set_bb_gain(20, 0)
        self.osmosdr_source_0.set_antenna('', 0)
        self.osmosdr_source_0.set_bandwidth(0, 0)
        self.low_pass_filter_0 = filter.fir_filter_ccf(
            N,
            firdes.low_pass(
                1,
                samp_rate,
                samp_rate/N/2,
                samp_rate/N/2,
                window.WIN_HAMMING,
                6.76))
        self.freq_xlating_fir_filter_xxx_0_1 = filter.freq_xlating_fir_filter_ccc(N, taps, 200000, samp_rate)
        self.freq_xlating_fir_filter_xxx_0_0 = filter.freq_xlating_fir_filter_ccc(N, taps, -125000, samp_rate)
        self.freq_xlating_fir_filter_xxx_0 = filter.freq_xlating_fir_filter_ccc(N, taps, 200000-25000, samp_rate)
        self.analog_am_demod_cf_3 = analog.am_demod_cf(
        	channel_rate=samp_rate/N,
        	audio_decim=int(24/N),
        	audio_pass=5000,
        	audio_stop=5500,
        )
        self.analog_am_demod_cf_2 = analog.am_demod_cf(
        	channel_rate=samp_rate/N,
        	audio_decim=int(24/N),
        	audio_pass=5000,
        	audio_stop=5500,
        )
        self.analog_am_demod_cf_1 = analog.am_demod_cf(
        	channel_rate=samp_rate/N,
        	audio_decim=int(24/N),
        	audio_pass=5000,
        	audio_stop=5500,
        )
        self.analog_am_demod_cf_0 = analog.am_demod_cf(
        	channel_rate=samp_rate/N,
        	audio_decim=int(24/N),
        	audio_pass=5000,
        	audio_stop=5500,
        )
        self.acars_acars_3 = acars.acars(3, '/tmp/logm125', False)
        self.acars_acars_2 = acars.acars(3, '/tmp/logp175', False)
        self.acars_acars_1 = acars.acars(3, '/tmp/logp200', False)
        self.acars_acars_0 = acars.acars(3, '/tmp/log0', False)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_am_demod_cf_0, 0), (self.acars_acars_0, 0))
        self.connect((self.analog_am_demod_cf_1, 0), (self.acars_acars_1, 0))
        self.connect((self.analog_am_demod_cf_2, 0), (self.acars_acars_2, 0))
        self.connect((self.analog_am_demod_cf_3, 0), (self.acars_acars_3, 0))
        self.connect((self.freq_xlating_fir_filter_xxx_0, 0), (self.analog_am_demod_cf_2, 0))
        self.connect((self.freq_xlating_fir_filter_xxx_0_0, 0), (self.analog_am_demod_cf_3, 0))
        self.connect((self.freq_xlating_fir_filter_xxx_0_1, 0), (self.analog_am_demod_cf_1, 0))
        self.connect((self.low_pass_filter_0, 0), (self.analog_am_demod_cf_0, 0))
        self.connect((self.osmosdr_source_0, 0), (self.freq_xlating_fir_filter_xxx_0, 0))
        self.connect((self.osmosdr_source_0, 0), (self.freq_xlating_fir_filter_xxx_0_0, 0))
        self.connect((self.osmosdr_source_0, 0), (self.freq_xlating_fir_filter_xxx_0_1, 0))
        self.connect((self.osmosdr_source_0, 0), (self.low_pass_filter_0, 0))


    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.set_taps(firdes.low_pass(1.0, self.samp_rate, self.samp_rate/self.N/2, self.samp_rate/self.N/2, window.WIN_HAMMING, 6.76))
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.samp_rate/self.N/2, self.samp_rate/self.N/2, window.WIN_HAMMING, 6.76))
        self.osmosdr_source_0.set_sample_rate(self.samp_rate)

    def get_N(self):
        return self.N

    def set_N(self, N):
        self.N = N
        self.set_taps(firdes.low_pass(1.0, self.samp_rate, self.samp_rate/self.N/2, self.samp_rate/self.N/2, window.WIN_HAMMING, 6.76))
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.samp_rate/self.N/2, self.samp_rate/self.N/2, window.WIN_HAMMING, 6.76))

    def get_taps(self):
        return self.taps

    def set_taps(self, taps):
        self.taps = taps
        self.freq_xlating_fir_filter_xxx_0.set_taps(self.taps)
        self.freq_xlating_fir_filter_xxx_0_0.set_taps(self.taps)
        self.freq_xlating_fir_filter_xxx_0_1.set_taps(self.taps)




def main(top_block_cls=example, options=None):
    tb = top_block_cls()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        sys.exit(0)

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    tb.start()

    try:
        input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
