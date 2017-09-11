@@ -296,9 +296,10 @@ class TreeModel {
     utils::Check(fi.Read(&param, sizeof(Param)) > 0,
                  "TreeModel: wrong format");
     nodes.resize(param.num_nodes); stats.resize(param.num_nodes);
-    utils::Check(fi.Read(&nodes[0], sizeof(Node) * nodes.size()) > 0,
+    utils::Assert(param.num_nodes != 0, "invalid model"); 
+    utils::Check(fi.Read(BeginPtr(nodes), sizeof(Node) * nodes.size()) > 0,
                  "TreeModel: wrong format");
-    utils::Check(fi.Read(&stats[0], sizeof(NodeStat) * stats.size()) > 0,
+    utils::Check(fi.Read(BeginPtr(stats), sizeof(NodeStat) * stats.size()) > 0,
                  "TreeModel: wrong format");
     if (param.size_leaf_vector != 0) {
       utils::Check(fi.Read(&leaf_vector), "TreeModel: wrong format");
@@ -322,8 +323,9 @@ class TreeModel {
     utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
                   "Tree::SaveModel");
     fo.Write(&param, sizeof(Param));
-    fo.Write(&nodes[0], sizeof(Node) * nodes.size());
-    fo.Write(&stats[0], sizeof(NodeStat) * nodes.size());
+    utils::Assert(param.num_nodes != 0, "invalid model"); 
+    fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
+    fo.Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
     if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
   }
   /*! 