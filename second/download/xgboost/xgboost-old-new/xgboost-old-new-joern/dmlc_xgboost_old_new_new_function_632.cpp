inline RowIter GetRow( size_t ridx, unsigned gid ) const{
                utils::Assert( gid == 0, "FMatrixS only have 1 column group" );
                return FMatrixS::GetRow( ridx );
            }