@@ -1,10 +1,16 @@
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
+#define NOMINMAX
 #include <cstring>
 #include "./updater.h"
 #include "./updater_prune-inl.hpp"
 #include "./updater_refresh-inl.hpp"
 #include "./updater_colmaker-inl.hpp"
+#ifndef XGBOOST_STRICT_CXX98_
+#include "./updater_sync-inl.hpp"
+#include "./updater_distcol-inl.hpp"
+#include "./updater_histmaker-inl.hpp"
+#endif
 
 namespace xgboost {
 namespace tree {
@@ -13,6 +19,11 @@ IUpdater* CreateUpdater(const char *name) {
   if (!strcmp(name, "prune")) return new TreePruner();
   if (!strcmp(name, "refresh")) return new TreeRefresher<GradStats>();
   if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
+#ifndef XGBOOST_STRICT_CXX98_
+  if (!strcmp(name, "sync")) return new TreeSyncher();
+  if (!strcmp(name, "grow_histmaker")) return new CQHistMaker<GradStats>();
+  if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();
+#endif
   utils::Error("unknown updater:%s", name);
   return NULL;
 }