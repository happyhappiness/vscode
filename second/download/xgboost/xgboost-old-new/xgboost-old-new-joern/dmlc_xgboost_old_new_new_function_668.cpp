inline RowIter GetRow( size_t ridx ) const{
                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
                RowIter it; 
                it.dptr_ = &row_data_[ row_ptr_[ridx] ] - 1;
                it.end_  = &row_data_[ row_ptr_[ridx+1] ] - 1;
                return it;
            }