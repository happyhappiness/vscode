             */
            inline void InitModel( void ){
                pred_buffer.clear(); pred_counter.clear();
                pred_buffer.resize ( param.num_pbuffer, 0.0 );
                pred_counter.resize( param.num_pbuffer, 0 );
                utils::Assert( param.num_boosters == 0 );
                utils::Assert( boosters.size() == 0 );
            }
            /*!
             * \brief initialize solver before training, called before training
             * this function is reserved for solver to allocate necessary space and do other preparation 
             */            
            inline void InitTrainer( void ){
                if( nthread != 0 ){
                    omp_set_num_threads( nthread );
                }
                // make sure all the boosters get the latest parameters
                for( size_t i = 0; i < this->boosters.size(); i ++ ){
