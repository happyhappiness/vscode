inline IObjFunction* CreateObjFunction( const char *name ){
<<<<<<< HEAD
            if( !strcmp("reg", name ) ) return new RegressionObj();
            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
            if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
            if( !strcmp("softmax", name ) ) return new SoftmaxMultiClassObj();
            if (!strcmp("rank:map", name)) return new LambdaRankObj_MAP();
            if (!strcmp("rank:ndcg", name)) return new LambdaRankObj_NDCG();
            utils::Error("unknown objective function type");
            return NULL;
        }