            }
        public:
            /*! 
             * \brief step 1: initialize the number of rows in the data
             * \nrows number of rows in the matrix 
             */
            inline void InitBudget( size_t nrows ){
                if( !UseAcList ){
                    rptr.resize( nrows + 1 );
                    std::fill( rptr.begin(), rptr.end(), 0 );
                }else{
                    Assert( nrows + 1 == rptr.size(), "rptr must be initialized already" );
                    this->Cleanup();
