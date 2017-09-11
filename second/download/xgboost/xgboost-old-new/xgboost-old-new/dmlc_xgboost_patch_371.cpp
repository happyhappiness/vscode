@@ -48,6 +48,7 @@ class IUpdater {
 }  // namespace xgboost
 
 #include "./updater_prune-inl.hpp"
+#include "./updater_refresh-inl.hpp"
 #include "./updater_colmaker-inl.hpp"
 
 namespace xgboost {
@@ -60,6 +61,7 @@ namespace tree {
 template<typename FMatrix>
 inline IUpdater<FMatrix>* CreateUpdater(const char *name) {
   if (!strcmp(name, "prune")) return new TreePruner<FMatrix>();
+  if (!strcmp(name, "refresh")) return new TreeRefresher<FMatrix>();
   if (!strcmp(name, "grow_colmaker")) return new ColMaker<FMatrix, GradStats>();
   utils::Error("unknown updater:%s", name);
   return NULL;