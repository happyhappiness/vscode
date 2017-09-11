inline size_t NumCol( void ) const{
                utils::Assert( this->HaveColAccess() );
                return col_ptr_.size() - 1;
            }