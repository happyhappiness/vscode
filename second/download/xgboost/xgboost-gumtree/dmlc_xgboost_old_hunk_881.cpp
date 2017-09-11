                sp.len = static_cast<bst_uint>( row_ptr_[ sidx + 1 ] - row_ptr_[ sidx ] );
                sp.data_ = &row_data_[ row_ptr_[ sidx ] ];
                return sp;
            }            
            /*!  \brief get row iterator*/
            inline RowIter GetRow( size_t ridx ) const{
                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
                RowIter it; 
                it.dptr = &row_data_[ row_ptr_[ridx] ] - 1;
                it.dptr = &row_data_[ row_ptr_[ridx+1] ] - 1;
                return it;
            }
            /*! 
             * \brief add a row to the matrix, with data stored in STL container
