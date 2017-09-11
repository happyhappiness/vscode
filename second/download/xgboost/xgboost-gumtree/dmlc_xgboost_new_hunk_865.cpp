    namespace booster{
        /*! \brief node statistics used in regression tree */
        struct RTreeNodeStat{
            /*! \brief loss chg caused by current split */
            float loss_chg;
            /*! \brief sum of hessian values, used to measure coverage of data */
            float sum_hess;
            /*! \brief weight of current node */
            float base_weight;
            /*! \brief number of child that is leaf node known up to now */
            int   leaf_child_cnt;
            /*! \brief print information of current stats to fo */
            inline void Print( FILE *fo, bool is_leaf ) const{
                if( !is_leaf ){
                    fprintf( fo, "gain=%f,cover=%f", loss_chg, sum_hess );
                }else{
                    fprintf( fo, "cover=%f", sum_hess );
                }
            }
        };
        /*! \brief most comment structure of regression tree */
        class RegTree: public TreeModel<bst_float,RTreeNodeStat>{
