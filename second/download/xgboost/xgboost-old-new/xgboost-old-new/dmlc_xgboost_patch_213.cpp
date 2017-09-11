@@ -304,11 +304,12 @@ class TreeModel {
     }
     // chg deleted nodes
     deleted_nodes.resize(0);
-    for (int i = param.num_roots; i < param.num_nodes; i ++) {
+    for (int i = param.num_roots; i < param.num_nodes; ++i) {
       if (nodes[i].is_deleted()) deleted_nodes.push_back(i);
     }
     utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
-                  "number of deleted nodes do not match");
+                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
+                  param.num_deleted, deleted_nodes.size(), param.num_nodes);
   }
   /*! 
    * \brief save model to stream