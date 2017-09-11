            }
        public:
            /*! 
             * \brief step 1: initialize the number of rows in the data, not necessary exact
             * \nrows number of rows in the matrix, can be smaller than expected
             */
            inline void InitBudget( size_t nrows = 0 ){
                if( !UseAcList ){
                    rptr.clear();
                    rptr.resize( nrows + 1, 0 );
                }else{
                    Assert( nrows + 1 == rptr.size(), "rptr must be initialized already" );
                    this->Cleanup();
