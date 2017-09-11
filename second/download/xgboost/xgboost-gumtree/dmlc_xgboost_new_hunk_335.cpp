#ifndef XGBOOST_STRICT_CXX98_
  if (!strcmp(name, "sync")) return new TreeSyncher();
  if (!strcmp(name, "grow_histmaker")) return new CQHistMaker<GradStats>();
  if (!strcmp(name, "grow_skmaker")) return new SketchMaker();
  if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();
#endif
  utils::Error("unknown updater:%s", name);
