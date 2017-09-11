         *    (3) model.InitTrainer before calling model.Predict and model.DoBoost
         *    (4) model.Predict to get predictions given a instance
         *    (4) model.DoBoost to update the ensembles, add new booster to the model
         *    (4) model.SaveModel to save learned results 
         *
         *  Bufferring: each instance comes with a buffer_index in Predict. 
         *              when mparam.num_pbuffer != 0, a unique buffer index can be 
         *              assigned to each instance to buffer previous results of boosters,
         *              this helps to speedup training, so consider assign buffer_index 
         *              for each training instances, if buffer_index = -1, the code
         *              recalculate things from scratch and will still works correctly
         */
        class GBMBase{
        public:
            /*! \brief number of thread used */
            GBMBase( void ){}
            /*! \brief destructor */
            virtual ~GBMBase( void ){
                this->FreeSpace();
            }
            /*! 
             * \brief set parameters from outside 
             * \param name name of the parameter
             * \param val  value of the parameter
             */
            inline void SetParam( const char *name, const char *val ){
                if( !strncmp( name, "bst:", 4 ) ){
                    cfg.PushBack( name + 4, val );
                }
                if( !strcmp( name, "silent") ){
                    cfg.PushBack( name, val );
                }
                tparam.SetParam( name, val );
                if( boosters.size() == 0 ) mparam.SetParam( name, val );
            }
            /*! 
             * \brief load model from stream
             * \param fi input stream
             */
            inline void LoadModel( utils::IStream &fi ){
                if( boosters.size() != 0 ) this->FreeSpace();
                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
                boosters.resize( mparam.num_boosters );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ] = booster::CreateBooster<FMatrixS>( mparam.booster_type );
                    boosters[ i ]->LoadModel( fi );
                }
                {// load info 
                    booster_info.resize( mparam.num_boosters );
                    if( mparam.num_boosters != 0 ){
                        utils::Assert( fi.Read( &booster_info[0], sizeof(int)*mparam.num_boosters ) != 0 );
                    }
                }
                if( mparam.num_pbuffer != 0 ){
                    pred_buffer.resize ( mparam.num_pbuffer );
                    pred_counter.resize( mparam.num_pbuffer );
                    utils::Assert( fi.Read( &pred_buffer[0] , pred_buffer.size()*sizeof(float) ) != 0 );
                    utils::Assert( fi.Read( &pred_counter[0], pred_counter.size()*sizeof(unsigned) ) != 0 );
                }
            }
            /*! 
             * \brief save model to stream
             * \param fo output stream
             */
            inline void SaveModel( utils::IStream &fo ) const {
                utils::Assert( mparam.num_boosters == (int)boosters.size() );
                fo.Write( &mparam, sizeof(ModelParam) );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ]->SaveModel( fo ); 
                }
                if( booster_info.size() != 0 ){
                    fo.Write( &booster_info[0], sizeof(int) * booster_info.size() );
                }
                if( mparam.num_pbuffer != 0 ){
                    fo.Write( &pred_buffer[0] , pred_buffer.size()*sizeof(float) );
                    fo.Write( &pred_counter[0], pred_counter.size()*sizeof(unsigned) );
                }
            }
            /*!
             * \brief initialize the current data storage for model, if the model is used first time, call this function
             */
            inline void InitModel( void ){
                pred_buffer.clear(); pred_counter.clear();
                pred_buffer.resize ( mparam.num_pbuffer, 0.0 );
                pred_counter.resize( mparam.num_pbuffer, 0 );
                utils::Assert( mparam.num_boosters == 0 );
                utils::Assert( boosters.size() == 0 );
            }
            /*!
             * \brief initialize solver before training, called before training
             * this function is reserved for solver to allocate necessary space and do other preparation 
             */            
            inline void InitTrainer( void ){
                if( tparam.nthread != 0 ){
                    omp_set_num_threads( tparam.nthread );
                }
                // make sure all the boosters get the latest parameters
                for( size_t i = 0; i < this->boosters.size(); i ++ ){
                    this->ConfigBooster( this->boosters[i] );
                }
            }
            /*! 
             * \brief DumpModel
             * \param fo text file 
             * \param fmap feature map that may help give interpretations of feature
             * \param with_stats whether print statistics
             */            
            inline void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    fprintf( fo, "booster[%d]\n", (int)i );
                    boosters[i]->DumpModel( fo, fmap, with_stats );
                }
            }
            /*! 
             * \brief Dump path of all trees
             * \param fo text file 
             * \param data input data
             */
            inline void DumpPath( FILE *fo, const FMatrixS &data ){
                for( size_t i = 0; i < data.NumRow(); ++ i ){
                    for( size_t j = 0; j < boosters.size(); ++ j ){
                        if( j != 0 ) fprintf( fo, "\t" );
                        std::vector<int> path;
                        boosters[j]->PredPath( path, data, i );
                        fprintf( fo, "%d", path[0] );
                        for( size_t k = 1; k < path.size(); ++ k ){
                            fprintf( fo, ",%d", path[k] );
                        }
                    }
                    fprintf( fo, "\n" );
                }
            }
        public:
            /*! 
             * \brief do gradient boost training for one step, using the information given
             *        Note: content of grad and hess can change after DoBoost
             * \param grad first order gradient of each instance
             * \param hess second order gradient of each instance
             * \param feats features of each instance
             * \param root_index pre-partitioned root index of each instance, 
             *          root_index.size() can be 0 which indicates that no pre-partition involved
             */
            inline void DoBoost( std::vector<float> &grad,
                                 std::vector<float> &hess,
                                 const booster::FMatrixS &feats,
                                 const std::vector<unsigned> &root_index ) {
                booster::IBooster *bst = this->GetUpdateBooster();
                bst->DoBoost( grad, hess, feats, root_index );
            }
            /*! 
             * \brief predict values for given sparse feature vector
             *   NOTE: in tree implementation, this is only OpenMP threadsafe, but not threadsafe
             * \param feats feature matrix
             * \param row_index  row index in the feature matrix
             * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
             * \param root_index root id of current instance, default = 0
             * \return prediction 
             */
            inline float Predict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                size_t istart = 0;
                float  psum = 0.0f;

                // load buffered results if any
                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                    utils::Assert( buffer_index < mparam.num_pbuffer, "buffer index exceed num_pbuffer" );
                    istart = this->pred_counter[ buffer_index ];
                    psum   = this->pred_buffer [ buffer_index ];
                }
            
                for( size_t i = istart; i < this->boosters.size(); i ++ ){
                    psum += this->boosters[ i ]->Predict( feats, row_index, root_index );
                }                
                // updated the buffered results
                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                    this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
                    this->pred_buffer [ buffer_index ] = psum;
                }
                return psum;
            }
        public:
            //--------trial code for interactive update an existing booster------
            //-------- usually not needed, ignore this region ---------
            /*! 
             * \brief same as Predict, but removes the prediction of booster to be updated 
             *        this function must be called once and only once for every data with pbuffer
             */
            inline float InteractPredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                float psum = this->Predict( feats, row_index, buffer_index, root_index );
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    psum -= boosters[ bid ]->Predict( feats, row_index, root_index );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] = psum;
                    }
                }
                return psum;
            }
            /*! \brief delete the specified booster */
            inline void DelteBooster( void ){
                const int bid = tparam.reupdate_booster;
                utils::Assert( bid >= 0 && bid < mparam.num_boosters , "must specify booster index for deletion"); 
                delete boosters[ bid ];
                for( int i = bid + 1; i < mparam.num_boosters; ++ i ){
                    boosters[i-1] = boosters[ i ];
                    booster_info[i-1] = booster_info[ i ];
                } 
                boosters.resize( mparam.num_boosters -= 1 );
                booster_info.resize( boosters.size() );
            }
            /*! \brief update the prediction buffer, after booster have been updated */            
            inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] += boosters[ bid ]->Predict( feats, row_index, root_index );
                    }
                }
            }
            //-----------non public fields afterwards-------------
        protected:
            /*! \brief free space of the model */
            inline void FreeSpace( void ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    delete boosters[i];
                }
                boosters.clear(); booster_info.clear(); mparam.num_boosters = 0; 
            }
            /*! \brief configure a booster */
            inline void ConfigBooster( booster::IBooster *bst ){
                cfg.BeforeFirst();
                while( cfg.Next() ){
                    bst->SetParam( cfg.name(), cfg.val() );
                }
            }
            /*! 
             * \brief get a booster to update 
             * \return the booster created
             */
            inline booster::IBooster *GetUpdateBooster( void ){
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    this->ConfigBooster( boosters[bid] );
                    return boosters[ bid ];
                }

                if( mparam.do_reboost == 0 || boosters.size() == 0 ){
                    mparam.num_boosters += 1;
                    boosters.push_back( booster::CreateBooster<FMatrixS>( mparam.booster_type ) );
                    booster_info.push_back( 0 );
                    this->ConfigBooster( boosters.back() );
                    boosters.back()->InitModel();                    
                }else{
                    this->ConfigBooster( boosters.back() );
                }
                return boosters.back();
            }
