           if( !strcmp("multi:softmax", name ) )      return new SoftmaxMultiClassObj();
           if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
           if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
           utils::Error("unknown objective function type");
           return NULL;
       }
    };
