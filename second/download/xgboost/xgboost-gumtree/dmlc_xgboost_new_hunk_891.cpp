                    this->ConfigBooster( this->boosters[i] );
                }
            }
            /*! 
             * \brief DumpModel
             * \param fo text file 
             */            
            inline void DumpModel( FILE *fo ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    fprintf( fo, "booster[%d]\n", (int)i );
                    boosters[i]->DumpModel( fo );
                }
            }
        public:
            /*! 
             * \brief do gradient boost training for one step, using the information given
