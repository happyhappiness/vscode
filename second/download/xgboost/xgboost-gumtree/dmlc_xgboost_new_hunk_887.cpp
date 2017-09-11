            inline void LoadBinary( utils::IStream &fi ){
                size_t nrow;
                utils::Assert( fi.Read( &nrow, sizeof(size_t) ) != 0, "Load FMatrixS" );
                row_ptr_.resize( nrow + 1 );
                utils::Assert( fi.Read( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) ), "Load FMatrixS" );

                row_data_.resize( row_ptr_.back() ); 
                if( row_data_.size() != 0 ){
                    utils::Assert( fi.Read( &row_data_[0] , row_data_.size() * sizeof(REntry) ) , "Load FMatrixS" );
                }
            }
        private:
            /*! \brief row pointer of CSR sparse storage */
            std::vector<size_t>  row_ptr_;
            /*! \brief data in the row */
            std::vector<REntry>  row_data_;
        };        
    };
};
#endif
