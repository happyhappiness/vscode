            /*! 
             * \brief dump model into text file
             * \param fo output stream 
             * \param fmap feature map that may help give interpretations of feature
             * \param with_stats whether print statistics
             */
            virtual void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats = false ){
                utils::Error( "not implemented" );                
            }
        public:
