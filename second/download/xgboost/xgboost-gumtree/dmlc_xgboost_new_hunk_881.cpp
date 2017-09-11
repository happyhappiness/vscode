                sp.len = static_cast<bst_uint>( row_ptr_[ sidx + 1 ] - row_ptr_[ sidx ] );
                sp.data_ = &row_data_[ row_ptr_[ sidx ] ];
                return sp;
            }
            /*! 
             * \brief add a row to the matrix, with data stored in STL container
