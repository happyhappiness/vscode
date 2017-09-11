@@ -62,8 +62,6 @@ inline IUpdater<FMatrix>* CreateUpdater(const char *name) {
   if (!strcmp(name, "prune")) return new TreePruner<FMatrix>();
   if (!strcmp(name, "refresh")) return new TreeRefresher<FMatrix, GradStats>();
   if (!strcmp(name, "grow_colmaker")) return new ColMaker<FMatrix, GradStats>();
-  if (!strcmp(name, "grow_colmaker2")) return new ColMaker<FMatrix, CVGradStats<2> >();
-  if (!strcmp(name, "grow_colmaker5")) return new ColMaker<FMatrix, CVGradStats<5> >();
   utils::Error("unknown updater:%s", name);
   return NULL;
 }