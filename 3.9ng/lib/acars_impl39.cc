/* -*- c++ -*- */
/*
 * Copyright 2022 gr-acars author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "acars_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace acars {

#pragma message("set the following appropriately and remove this warning")
using input_type = float;
acars::sptr acars::make(jmf) { return gnuradio::make_block_sptr<acars_impl>(jmf); }


/*
 * The private constructor
 */
acars_impl::acars_impl(jmf)
    : gr::sync_block("acars",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(0, 0, 0))
{
}

/*
 * Our virtual destructor.
 */
acars_impl::~acars_impl() {}

int acars_impl::work(int noutput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);

#pragma message("Implement the signal processing in your block and remove this warning")
    // Do <+signal processing+>

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace acars */
} /* namespace gr */
