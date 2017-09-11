@@ -110,6 +110,10 @@ class TreeModel {
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
@@ -144,7 +148,11 @@ class TreeModel {
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
@@ -197,11 +205,11 @@ class TreeModel {
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
 