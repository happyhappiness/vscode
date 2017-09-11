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
