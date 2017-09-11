                unsigned cnt = 0;
                for( size_t i = 0; i < findex.size(); i ++ ){
                    if( findex[i] < fstart || findex[i] >= fend ) continue;
                    REntry e; e.findex = findex[i]; e.fvalue = fvalue[i];
                    row_data_.push_back( e );
                    cnt ++;
                }
                row_ptr_.push_back( row_ptr_.back() + cnt );
                return row_ptr_.size() - 2;
            }
        public:
            /*!
             * \brief save data to binary stream 
             *        note: since we have size_t in row_ptr, 
             *              the function is not consistent between 64bit and 32bit machine
             * \param fo output stream
             */
			inline void SaveBinary(utils::IStream &fo ) const{
                size_t nrow = this->NumRow();
                fo.Write( &nrow, sizeof(size_t) );
                fo.Write( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) );
                if( row_data_.size() != 0 ){
                    fo.Write( &row_data_[0] , row_data_.size() * sizeof(REntry) );
                }
            }
            /*!
             * \brief load data from binary stream 
             *        note: since we have size_t in row_ptr, 
             *              the function is not consistent between 64bit and 32bit machine
             * \param fi output stream
             */
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
