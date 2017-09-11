@@ -7,6 +7,7 @@
 #include "./updater_refresh-inl.hpp"
 #include "./updater_colmaker-inl.hpp"
 #include "./updater_distcol-inl.hpp"
+#include "./updater_skmaker-inl.hpp"
 #include "./updater_histmaker-inl.hpp"
 
 namespace xgboost {
@@ -19,6 +20,7 @@ IUpdater* CreateUpdater(const char *name) {
   if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
   if (!strcmp(name, "grow_qhistmaker")) return new QuantileHistMaker<GradStats>();
   if (!strcmp(name, "grow_cqmaker")) return new CQHistMaker<GradStats>();
+  if (!strcmp(name, "grow_skmaker")) return new SketchMaker();
   if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();
 
   utils::Error("unknown updater:%s", name);