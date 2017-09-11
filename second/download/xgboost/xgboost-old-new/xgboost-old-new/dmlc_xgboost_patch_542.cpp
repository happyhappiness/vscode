@@ -68,65 +68,65 @@ namespace xgboost{
                 };
             private:
                 // pointer to parent, highest bit is used to indicate whether it's a left child or not 
-                int sparent;
+                int parent_;
                 // pointer to left, right
-                int left, right;
+                int cleft_, cright_;
                 // split feature index, left split or right split depends on the highest bit
-                unsigned sindex;            
+                unsigned sindex_;            
                 // extra info
-                Info info;
+                Info info_;
             private:
                 inline void set_parent( int pidx, bool is_left_child = true ){
                     if( is_left_child ) pidx |= (1U << 31);
-                    this->sparent = pidx;
+                    this->parent_ = pidx;
                 }
             public:
                 /*! \brief index of left child */
                 inline int cleft( void ) const{
-                    return this->left;
+                    return this->cleft_;
                 }
                 /*! \brief index of right child */
                 inline int cright( void ) const{
-                    return this->right;
+                    return this->cright_;
                 }
                 /*! \brief feature index of split condition */
                 inline unsigned split_index( void ) const{
-                    return sindex & ( (1U<<31) - 1U );
+                    return sindex_ & ( (1U<<31) - 1U );
                 }
                 /*! \brief when feature is unknown, whether goes to left child */
                 inline bool default_left( void ) const{
-                    return (sindex >> 31) != 0;
+                    return (sindex_ >> 31) != 0;
                 } 
                 /*! \brief whether current node is leaf node */
                 inline bool is_leaf( void ) const{
-                    return left == -1;
+                    return cleft_ == -1;
                 }
                 /*! \brief get leaf value of leaf node */
                 inline float leaf_value( void ) const{
-                    return (this->info).leaf_value;
+                    return (this->info_).leaf_value;
                 }
                 /*! \brief get split condition of the node */
                 inline TSplitCond split_cond( void ) const{
-                    return (this->info).split_cond;
+                    return (this->info_).split_cond;
                 }
                 /*! \brief get parent of the node */
                 inline int parent( void ) const{
-                    return sparent & ( (1U << 31) - 1 );
+                    return parent_ & ( (1U << 31) - 1 );
                 } 
                 /*! \brief whether current node is left child */
                 inline bool is_left_child( void ) const{
-                    return ( sparent & (1U << 31)) != 0;
+                    return ( parent_ & (1U << 31)) != 0;
                 }
                 /*! \brief whether current node is root */
                 inline bool is_root( void ) const{
-                    return sparent == -1;
+                    return parent_ == -1;
                 }
                 /*! 
                  * \brief set the right child 
                  * \param nide node id to right child
                  */
                 inline void set_right_child( int nid ){
-                    this->right = nid;
+                    this->cright_ = nid;
                 }
                 /*! 
                  * \brief set split condition of current node 
@@ -136,8 +136,8 @@ namespace xgboost{
                  */
                 inline void set_split( unsigned split_index, TSplitCond split_cond, bool default_left = false ){
                     if( default_left ) split_index |= (1U << 31);
-                    this->sindex = split_index;
-                    (this->info).split_cond = split_cond;
+                    this->sindex_ = split_index;
+                    (this->info_).split_cond = split_cond;
                 }
                 /*! 
                  * \brief set the leaf value of the node
@@ -146,9 +146,9 @@ namespace xgboost{
                  *        additional information
                  */
                 inline void set_leaf( float value, int right = -1 ){
-                    (this->info).leaf_value = value;
-                    this->left = -1;
-                    this->right = right;
+                    (this->info_).leaf_value = value;
+                    this->cleft_ = -1;
+                    this->cright_ = right;
                 }
             };
         protected:
@@ -187,10 +187,10 @@ namespace xgboost{
              * \param new leaf value
              */
             inline void ChangeToLeaf( int rid, float value ){
-                utils::Assert( nodes[ nodes[rid].left  ].is_leaf(), "can not delete a non termial child");
-                utils::Assert( nodes[ nodes[rid].right ].is_leaf(), "can not delete a non termial child");
-                this->DeleteNode( nodes[ rid ].left ); 
-                this->DeleteNode( nodes[ rid ].right );
+                utils::Assert( nodes[ nodes[rid].cleft()  ].is_leaf(), "can not delete a non termial child");
+                utils::Assert( nodes[ nodes[rid].cright() ].is_leaf(), "can not delete a non termial child");
+                this->DeleteNode( nodes[ rid ].cleft() ); 
+                this->DeleteNode( nodes[ rid ].cright() );
                 nodes[ rid ].set_leaf( value );
             }
         public:
@@ -253,10 +253,10 @@ namespace xgboost{
             inline void AddChilds( int nid ){
                 int pleft  = this->AllocNode();
                 int pright = this->AllocNode();
-                nodes[ nid ].left  = pleft;
-                nodes[ nid ].right = pright;
-                nodes[ nodes[ nid ].left  ].set_parent( nid, true );
-                nodes[ nodes[ nid ].right ].set_parent( nid, false );
+                nodes[ nid ].cleft_  = pleft;
+                nodes[ nid ].cright_ = pright;
+                nodes[ nodes[ nid ].cleft()  ].set_parent( nid, true );
+                nodes[ nodes[ nid ].cright() ].set_parent( nid, false );
             }
             /*! 
              * \brief only add a right child to a leaf node 