inline void ParseRange( const char *val, int &a, int &b ){
                if( sscanf( val, "%d-%d", &a, &b ) == 2 ) return;
                utils::Assert( sscanf( val, "%d", &a ) == 1 );
                b = a + 1;
            }