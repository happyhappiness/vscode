    namespace regrank{        
        IObjFunction* CreateObjFunction( const char *name ){
            if( !strcmp("reg", name ) ) return new RegressionObj();
            utils::Error("unknown objective function type");
            return NULL;
        }
