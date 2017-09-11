                it.end_  = &col_data_[ col_ptr_[cidx+1] ] - 1;
                return it;
            }
            /*!
             * \brief intialize the data so that we have both column and row major
             *        access, call this whenever we need column access
