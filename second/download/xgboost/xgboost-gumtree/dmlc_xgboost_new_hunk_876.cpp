                it.end_  = &col_data_[ col_ptr_[cidx+1] ] - 1;
                return it;
            }
            /*!  \brief get col iterator */
            inline ColIter GetReverseSortedCol( size_t cidx ) const{
                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
                ColIter it; 
                it.dptr_ = &col_data_[ col_ptr_[cidx+1] ];
                it.end_  = &col_data_[ col_ptr_[cidx] ];
                return it;
            }
            /*!
             * \brief intialize the data so that we have both column and row major
             *        access, call this whenever we need column access
