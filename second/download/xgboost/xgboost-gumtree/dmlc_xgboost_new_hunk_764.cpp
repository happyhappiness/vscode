        IObjFunction* CreateObjFunction( const char *name ){
            if( !strcmp("reg", name ) ) return new RegressionObj();
            if( !strcmp("rank", name ) ) return new PairwiseRankObj();
            if( !strcmp("softmax", name ) ) return new SoftmaxObj();
            utils::Error("unknown objective function type");
            return NULL;
        }
