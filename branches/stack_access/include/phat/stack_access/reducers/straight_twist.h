/*  Copyright 2013 IST Austria
    Contributed by: Ulrich Bauer, Michael Kerber, Jan Reininghaus

    This file is part of PHAT.

    PHAT is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PHAT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PHAT.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include <phat/common/basic_types.h>
#include <phat/stack_access/boundary_matrix.h>
#include <phat/common/const_boundary_matrix.h>

namespace phat { namespace stack_access { namespace reducers {
    class straight_twist {

    public:
        template< typename Representation, typename InputBoundaryMatrix >
        void operator() ( const InputBoundaryMatrix& input_matrix, boundary_matrix< Representation >& reduced_matrix ) {

            const index nr_columns = input_matrix.get_num_cols();
            std::vector< index > lowest_one_lookup( nr_columns, -1 );
            column temp_col;
            reduced_matrix.init( nr_columns );
            for( index cur_col = 0; cur_col < nr_columns; cur_col++ ) {
                if( lowest_one_lookup[ cur_col ] != -1 ) {
                    temp_col.clear();
                    reduced_matrix.push_col( temp_col, input_matrix.get_dim( cur_col ) );
                } else {
                    input_matrix.get_col( cur_col, temp_col );
                    reduced_matrix.push_col( temp_col, input_matrix.get_dim( cur_col ) );
                    index lowest_one = reduced_matrix.get_max_index( cur_col );
                    while( lowest_one != -1 && lowest_one_lookup[ lowest_one ] != -1 ) {
                        reduced_matrix.add_to_top( lowest_one_lookup[ lowest_one ] );
                        lowest_one = reduced_matrix.get_max_index( cur_col );
                    }
                    if( lowest_one != -1 )
                        lowest_one_lookup[ lowest_one ] = cur_col;
                }
            }
        }
    };
} } }