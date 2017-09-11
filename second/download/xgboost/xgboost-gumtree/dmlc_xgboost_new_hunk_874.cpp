                return it;
            }
            /*!  \brief get col iterator */
            inline ColBackIter GetReverseSortedCol( size_t cidx ) const{
                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
                ColBackIter it; 
                it.dptr_ = &col_data_[ col_ptr_[cidx+1] ];
                it.end_  = &col_data_[ col_ptr_[cidx] ];
                return it;
