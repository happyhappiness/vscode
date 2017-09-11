            inline void LoadBinary( utils::IStream &fi ){
                size_t nrow;
                utils::Assert( fi.Read( &nrow, sizeof(size_t) ) != 0, "Load FMatrixS" );
                row_ptr.resize( nrow + 1 );
                utils::Assert( fi.Read( &row_ptr[0], row_ptr.size() * sizeof(size_t) ), "Load FMatrixS" );

                findex.resize( row_ptr.back() ); fvalue.resize( row_ptr.back() );                
                if( findex.size() != 0 ){
                    utils::Assert( fi.Read( &findex[0] , findex.size() * sizeof(bst_uint) ) , "Load FMatrixS" );
                    utils::Assert( fi.Read( &fvalue[0] , fvalue.size() * sizeof(bst_float) ), "Load FMatrixS" );
                }
            }
        };
    };    
};

#endif
