@@ -68,8 +68,9 @@ class TreeModel {
     }
   };
   /*! \brief tree node */
-  class Node{
+  class Node {
    public:
+	Node(void) : sindex_(0) {}
     /*! \brief index of left child */
     inline int cleft(void) const {
       return this->cleft_;
@@ -110,6 +111,10 @@ class TreeModel {
     inline bool is_left_child(void) const {
       return (parent_ & (1U << 31)) != 0;
     }
+    /*! \brief whether this node is deleted */
+    inline bool is_deleted(void) const {
+      return sindex_ == std::numeric_limits<unsigned>::max();
+    }
     /*! \brief whether current node is root */
     inline bool is_root(void) const {
       return parent_ == -1;
@@ -144,7 +149,11 @@ class TreeModel {
       this->cleft_ = -1;
       this->cright_ = right;
     }
-
+    /*! \brief mark that this node is deleted */
+    inline void mark_delete(void) {
+      this->sindex_ = std::numeric_limits<unsigned>::max();
+    }
+    
    private:
     friend class TreeModel<TSplitCond, TNodeStat>;
     /*! 
@@ -197,11 +206,11 @@ class TreeModel {
     leaf_vector.resize(param.num_nodes * param.size_leaf_vector); 
     return nd;
   }
-  // delete a tree node
+  // delete a tree node, keep the parent field to allow trace back
   inline void DeleteNode(int nid) {
     utils::Assert(nid >= param.num_roots, "can not delete root");
     deleted_nodes.push_back(nid);
-    nodes[nid].set_parent(-1);
+    nodes[nid].mark_delete();
     ++param.num_deleted;
   }
 
@@ -296,11 +305,12 @@ class TreeModel {
     }
     // chg deleted nodes
     deleted_nodes.resize(0);
-    for (int i = param.num_roots; i < param.num_nodes; i ++) {
-      if (nodes[i].is_root()) deleted_nodes.push_back(i);
+    for (int i = param.num_roots; i < param.num_nodes; ++i) {
+      if (nodes[i].is_deleted()) deleted_nodes.push_back(i);
     }
     utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
-                  "number of deleted nodes do not match");
+                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
+                  param.num_deleted, deleted_nodes.size(), param.num_nodes);
   }
   /*! 
    * \brief save model to stream