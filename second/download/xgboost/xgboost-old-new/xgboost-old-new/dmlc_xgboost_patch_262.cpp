@@ -13,6 +13,8 @@ IUpdater* CreateUpdater(const char *name) {
   if (!strcmp(name, "prune")) return new TreePruner();
   if (!strcmp(name, "refresh")) return new TreeRefresher<GradStats>();
   if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
+  if (!strcmp(name, "grow_colmaker5")) return new ColMaker< CVGradStats<5> >();
+  if (!strcmp(name, "grow_colmaker3")) return new ColMaker< CVGradStats<3> >();
   utils::Error("unknown updater:%s", name);
   return NULL;
 }