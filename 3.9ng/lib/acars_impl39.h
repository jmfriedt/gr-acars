/* -*- c++ -*- */
/*
 * Copyright 2022 gr-acars author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ACARS_ACARS_IMPL_H
#define INCLUDED_ACARS_ACARS_IMPL_H

#include <acars/acars.h>

namespace gr {
namespace acars {

class acars_impl : public acars
{
private:
    // Nothing to declare in this block.

public:
    acars_impl(jmf);
    ~acars_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace acars
} // namespace gr

#endif /* INCLUDED_ACARS_ACARS_IMPL_H */
