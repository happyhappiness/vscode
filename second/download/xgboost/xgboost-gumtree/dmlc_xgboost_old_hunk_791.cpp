                model_dir_path = "./";
                interact_action = "update";
            }
            ~RegBoostTask( void ){
                for( size_t i = 0; i < deval.size(); i ++ ){
                    delete deval[i];
                }
            }
        private:
            inline void InitData( void ){
                if( name_fmap != "NULL" ) fmap.LoadText( name_fmap.c_str() );
                if( task == "dump" ) return;
                if( task == "pred" || task == "dumppath" ){
                    data.CacheLoad( test_path.c_str(), silent!=0, use_buffer!=0 );
                }else{
                    // training 
                    data.CacheLoad( train_path.c_str(), silent!=0, use_buffer!=0 );
                    utils::Assert( eval_data_names.size() == eval_data_paths.size() );
                    for( size_t i = 0; i < eval_data_names.size(); ++ i ){
                        deval.push_back( new DMatrix() );
                        deval.back()->CacheLoad( eval_data_paths[i].c_str(), silent!=0, use_buffer!=0 );
                    }
                }
                learner.SetData( &data, deval, eval_data_names );
            }
            inline void InitLearner( void ){
                cfg.BeforeFirst();
                while( cfg.Next() ){
                    learner.SetParam( cfg.name(), cfg.val() );
                }
                if( model_in != "NULL" ){
                    utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
                    learner.LoadModel( fi );
                    fi.Close();
                }else{
                    utils::Assert( task == "train", "model_in not specified" );
                    learner.InitModel();
                }
                learner.InitTrainer();
            }
            inline void TaskTrain( void ){
                const time_t start    = time( NULL );
                unsigned long elapsed = 0;
                for( int i = 0; i < num_round; ++ i ){
                    elapsed = (unsigned long)(time(NULL) - start); 
                    if( !silent ) printf("boosting round %d, %lu sec elapsed\n", i , elapsed );
                    learner.UpdateOneIter( i );
                    learner.EvalOneIter( i );
                    if( save_period != 0 && (i+1) % save_period == 0 ){
                        this->SaveModel( i );
                    }
                    elapsed = (unsigned long)(time(NULL) - start); 
                }
                // always save final round
                if( save_period == 0 || num_round % save_period != 0 ){
                    if( model_out == "NULL" ){
                        this->SaveModel( num_round - 1 );
                    }else{
                        this->SaveModel( model_out.c_str() );
                    }
                }
                if( !silent ){
                    printf("\nupdating end, %lu sec in all\n", elapsed );
                }
            }
            inline void TaskEval( void ){
                learner.EvalOneIter( 0 );
            }
            inline void TaskInteractive( void ){
                const time_t start    = time( NULL );
                unsigned long elapsed = 0;
                int batch_action = 0;
                
                cfg_batch.BeforeFirst();
                while( cfg_batch.Next() ){
                    if( !strcmp( cfg_batch.name(), "run" ) ){
                        learner.UpdateInteract( interact_action );
                        batch_action += 1;
                    } else{
                        learner.SetParam( cfg_batch.name(), cfg_batch.val() );
                    }
                }

                if( batch_action == 0 ){
                    learner.UpdateInteract( interact_action );
                }
                utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                this->SaveModel( model_out.c_str() );
                elapsed = (unsigned long)(time(NULL) - start); 

                if( !silent ){
                    printf("\ninteractive update, %d batch actions, %lu sec in all\n", batch_action, elapsed );
                }
            }

            inline void TaskDump( void ){
                FILE *fo = utils::FopenCheck( name_dump.c_str(), "w" );
                learner.DumpModel( fo, fmap, dump_model_stats != 0 );
                fclose( fo );
            }
            inline void TaskDumpPath( void ){
                FILE *fo = utils::FopenCheck( name_dumppath.c_str(), "w" );
                learner.DumpPath( fo, data );
                fclose( fo );
            }
            inline void SaveModel( const char *fname ) const{
                utils::FileStream fo( utils::FopenCheck( fname, "wb" ) );
                learner.SaveModel( fo );
                fo.Close();
            }
            inline void SaveModel( int i ) const{
                char fname[256];
                sprintf( fname ,"%s/%04d.model", model_dir_path.c_str(), i+1 );
                this->SaveModel( fname );
            }
            inline void TaskPred( void ){
                std::vector<float> preds;
                if( !silent ) printf("start prediction...\n");
                learner.Predict( preds, data );
                if( !silent ) printf("writing prediction to %s\n", name_pred.c_str() );
                FILE *fo = utils::FopenCheck( name_pred.c_str(), "w" );
                for( size_t i = 0; i < preds.size(); i ++ ){
                    fprintf( fo, "%f\n", preds[i] );
                }
                fclose( fo );                
            }
        private:
            /* \brief whether silent */
            int silent;
            /* \brief whether use auto binary buffer */
            int use_buffer;
            /* \brief number of boosting iterations */
            int num_round;            
            /* \brief the period to save the model, 0 means only save the final round model */
            int save_period;
            /*! \brief interfact action */
