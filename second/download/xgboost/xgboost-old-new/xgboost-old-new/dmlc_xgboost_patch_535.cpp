@@ -89,6 +89,10 @@ namespace xgboost{
                 inline int cright( void ) const{
                     return this->cright_;
                 }
+                /*! \brief index of default child when feature is missing */
+                inline int cdefault( void ) const{
+                    return this->default_left() ? this->cleft() : this->cright();
+                }
                 /*! \brief feature index of split condition */
                 inline unsigned split_index( void ) const{
                     return sindex_ & ( (1U<<31) - 1U );
@@ -228,9 +232,10 @@ namespace xgboost{
              */
             inline void LoadModel( utils::IStream &fi ){
                 utils::Assert( fi.Read( &param, sizeof(Param) ) > 0, "TreeModel" );
-                nodes.resize( param.num_nodes );
+                nodes.resize( param.num_nodes ); stats.resize( param.num_nodes );
                 utils::Assert( fi.Read( &nodes[0], sizeof(Node) * nodes.size() ) > 0, "TreeModel::Node" );
-                
+                utils::Assert( fi.Read( &stats[0], sizeof(NodeStat) * stats.size() ) > 0, "TreeModel::Node" );
+
                 deleted_nodes.resize( 0 );
                 for( int i = param.num_roots; i < param.num_nodes; i ++ ){
                     if( nodes[i].is_root() ) deleted_nodes.push_back( i );
@@ -243,8 +248,10 @@ namespace xgboost{
              */
             inline void SaveModel( utils::IStream &fo ) const{
                 utils::Assert( param.num_nodes == (int)nodes.size() );
+                utils::Assert( param.num_nodes == (int)stats.size() );
                 fo.Write( &param, sizeof(Param) );
                 fo.Write( &nodes[0], sizeof(Node) * nodes.size() );
+                fo.Write( &stats[0], sizeof(NodeStat) * nodes.size() );
             }
             /*! 
              * \brief add child nodes to node
@@ -285,23 +292,50 @@ namespace xgboost{
                 return param.num_nodes - param.num_roots - param.num_deleted;
             }
             /*! \brief dump model to text file  */
-            inline void DumpModel( FILE *fo ){
-                this->Dump( 0, fo, 0 );
+            inline void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats ){
+                this->Dump( 0, fo, fmap, 0, with_stats );
             }
         private:
-            void Dump( int nid, FILE *fo, int depth ){
+            void Dump( int nid, FILE *fo, const utils::FeatMap& fmap, int depth, bool with_stats ){
                 for( int  i = 0;  i < depth; ++ i ){
                     fprintf( fo, "\t" );
                 }
                 if( nodes[ nid ].is_leaf() ){
-                    fprintf( fo, "%d:leaf=%f\n", nid, nodes[ nid ].leaf_value() );
+                    fprintf( fo, "%d:leaf=%f ", nid, nodes[ nid ].leaf_value() );
+                    if( with_stats ){
+                        stat( nid ).Print( fo, true );
+                    }
+                    fprintf( fo, "\n" );
                 }else{
                     // right then left,
                     TSplitCond cond = nodes[ nid ].split_cond();
-                    fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d\n", nid, 
-                             nodes[ nid ].split_index(), float(cond), nodes[ nid ].cleft(), nodes[ nid ].cright() );
-                    this->Dump( nodes[ nid ].cleft(), fo, depth+1 );
-                    this->Dump( nodes[ nid ].cright(), fo, depth+1 );
+                    const unsigned split_index = nodes[ nid ].split_index();
+
+                    if( split_index < fmap.size() ){
+                        if( fmap.type(split_index) == utils::FeatMap::kIndicator ){
+                            int nyes = nodes[ nid ].default_left()?nodes[nid].cright():nodes[nid].cleft();
+                            fprintf( fo, "%d:[%s] yes=%d,no=%d", 
+                                     nid, fmap.name( split_index ),
+                                     nyes, nodes[nid].cdefault() );                            
+                        }else{
+                            fprintf( fo, "%d:[%s<%f] yes=%d,no=%d,missing=%d", 
+                                     nid, fmap.name(split_index), float(cond), 
+                                     nodes[ nid ].cleft(), nodes[ nid ].cright(),
+                                     nodes[ nid ].cdefault() );
+                        }
+                    }else{
+                        fprintf( fo, "%d:[f%u<%f] yes=%d,no=%d,missing=%d", 
+                                 nid, split_index, float(cond), 
+                                 nodes[ nid ].cleft(), nodes[ nid ].cright(),
+                                 nodes[ nid ].cdefault() );
+                    }
+                    if( with_stats ){
+                        fprintf( fo, " ");
+                        stat( nid ).Print( fo, false );
+                    }
+                    fprintf( fo, "\n" );
+                    this->Dump( nodes[ nid ].cleft(), fo, fmap, depth+1, with_stats );
+                    this->Dump( nodes[ nid ].cright(), fo, fmap, depth+1, with_stats );
                 }                
             } 
         };
@@ -447,12 +481,22 @@ namespace xgboost{
     namespace booster{
         /*! \brief node statistics used in regression tree */
         struct RTreeNodeStat{
-            // loss chg caused by current split
+            /*! \brief loss chg caused by current split */
             float loss_chg;
-            // weight of current node
+            /*! \brief sum of hessian values, used to measure coverage of data */
+            float sum_hess;
+            /*! \brief weight of current node */
             float base_weight;
-            // number of child that is leaf node known up to now
+            /*! \brief number of child that is leaf node known up to now */
             int   leaf_child_cnt;
+            /*! \brief print information of current stats to fo */
+            inline void Print( FILE *fo, bool is_leaf ) const{
+                if( !is_leaf ){
+                    fprintf( fo, "gain=%f,cover=%f", loss_chg, sum_hess );
+                }else{
+                    fprintf( fo, "cover=%f", sum_hess );
+                }
+            }
         };
         /*! \brief most comment structure of regression tree */
         class RegTree: public TreeModel<bst_float,RTreeNodeStat>{