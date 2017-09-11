            inline static Type GetType( const char *tname ){
                if( !strcmp( "i", tname ) ) return kIndicator;        
                if( !strcmp( "q", tname ) ) return kQuantitive;
                if( !strcmp( "int", tname ) ) return kInteger;        
                if( !strcmp( "float", tname ) ) return kFloat;        
                utils::Error("unknown feature type, use i for indicator and q for quantity");
                return kIndicator;
            }
