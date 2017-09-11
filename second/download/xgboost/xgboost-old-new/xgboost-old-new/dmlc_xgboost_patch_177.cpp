@@ -10,6 +10,7 @@
 #include "./updater_sync-inl.hpp"
 #include "./updater_distcol-inl.hpp"
 #include "./updater_histmaker-inl.hpp"
+#include "./updater_skmaker-inl.hpp"
 #endif
 
 namespace xgboost {
@@ -22,6 +23,7 @@ IUpdater* CreateUpdater(const char *name) {
 #ifndef XGBOOST_STRICT_CXX98_
   if (!strcmp(name, "sync")) return new TreeSyncher();
   if (!strcmp(name, "grow_histmaker")) return new CQHistMaker<GradStats>();
+  if (!strcmp(name, "grow_skmaker")) return new SketchMaker();
   if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();
 #endif
   utils::Error("unknown updater:%s", name);