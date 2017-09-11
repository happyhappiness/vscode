  if (!strcmp(name, "sync")) return new TreeSyncher();
  if (!strcmp(name, "refresh")) return new TreeRefresher<GradStats>();
  if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
  //if (!strcmp(name, "grow_histmaker")) return new CQHistMaker<GradStats>();
  //if (!strcmp(name, "grow_skmaker")) return new SketchMaker();
  if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();

  utils::Error("unknown updater:%s", name);
