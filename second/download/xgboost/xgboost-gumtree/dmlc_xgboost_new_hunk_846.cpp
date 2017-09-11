            /*!  \brief get col iterator*/
            inline ColIter GetSortedCol( size_t cidx ) const{
                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
                return ColIter( &col_data_[ col_ptr_[cidx] ] - 1, &col_data_[ col_ptr_[cidx+1] ] - 1 );
            }
            /*!  \brief get col iterator */
            inline ColBackIter GetReverseSortedCol( size_t cidx ) const{
                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
                return ColBackIter( &col_data_[ col_ptr_[cidx+1] ], &col_data_[ col_ptr_[cidx] ] );
            }
            /*!
             * \brief intialize the data so that we have both column and row major
