            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
            if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
            if( !strcmp("softmax", name ) ) return new SoftmaxMultiClassObj();
            utils::Error("unknown objective function type");
            return NULL;
        }
