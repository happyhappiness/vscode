    namespace regrank{        
        IObjFunction* CreateObjFunction( const char *name ){
            if( !strcmp("reg", name ) ) return new RegressionObj();
            if( !strcmp("rank", name ) ) return new PairwiseRankObj();
            utils::Error("unknown objective function type");
            return NULL;
        }
