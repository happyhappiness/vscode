namespace xgboost{
    /*! \brief namespace for helper utils of the project */
    namespace utils{
        inline void Error( const char *msg ){
            fprintf( stderr, "Error:%s\n",msg );
            exit( -1 );
        }
        
        inline void Assert( bool exp ){
            if( !exp ) Error( "AssertError" );
        }
        
        inline void Assert( bool exp, const char *msg ){
            if( !exp ) Error( msg );
        }

        inline void Warning( const char *msg ){
            fprintf( stderr, "warning:%s\n",msg );
        }

        /*! \brief replace fopen, report error when the file open fails */
        inline FILE *FopenCheck( const char *fname , const char *flag ){
            FILE *fp = fopen64( fname , flag );
            if( fp == NULL ){
                fprintf( stderr, "can not open file \"%s\"\n",fname );
                exit( -1 );
            }
            return fp;
        }
        
        /*! \brief replace fopen, */
        inline FILE *FopenTry( const char *fname , const char *flag ){
            FILE *fp = fopen64( fname , flag );
            if( fp == NULL ){
                fprintf( stderr, "can not open file \"%s\"\n",fname );
                exit( -1 );
            }
            return fp;
        }
