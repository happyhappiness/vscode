            inline static Type GetType( const char *tname ){
                if( !strcmp( "i", tname ) ) return kIndicator;        
                if( !strcmp( "q", tname ) ) return kQuantitive;
                utils::Error("unknown feature type, use i for indicator and q for quantity");
                return kIndicator;
            }
