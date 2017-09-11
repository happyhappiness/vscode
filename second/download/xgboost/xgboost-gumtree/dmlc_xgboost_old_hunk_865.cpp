    namespace booster{
        /*! \brief node statistics used in regression tree */
        struct RTreeNodeStat{
            // loss chg caused by current split
            float loss_chg;
            // weight of current node
            float base_weight;
            // number of child that is leaf node known up to now
            int   leaf_child_cnt;
        };
        /*! \brief most comment structure of regression tree */
        class RegTree: public TreeModel<bst_float,RTreeNodeStat>{
