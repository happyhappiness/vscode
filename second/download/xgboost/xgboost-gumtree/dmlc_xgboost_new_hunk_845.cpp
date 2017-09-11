            /*!  \brief get row iterator*/
            inline RowIter GetRow( size_t ridx ) const{
                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
                return RowIter( &row_data_[ row_ptr_[ridx] ] - 1, &row_data_[ row_ptr_[ridx+1] ] - 1 );
            }
            /*!  \brief get row iterator*/
            inline RowIter GetRow( size_t ridx, unsigned gid ) const{
                utils::Assert( gid == 0, "FMatrixS only have 1 column group" );
                return FMatrixS::GetRow( ridx );
            }
        public:
            /*! \return whether column access is enabled */
