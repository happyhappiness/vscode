  if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
  if (!strcmp(name, "grow_qhistmaker")) return new QuantileHistMaker<GradStats>();
  if (!strcmp(name, "grow_cqmaker")) return new CQHistMaker<GradStats>();
  if (!strcmp(name, "grow_chistmaker")) return new ColumnHistMaker<GradStats>();
  if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();
  if (!strcmp(name, "grow_colmaker5")) return new ColMaker< CVGradStats<5> >();
  if (!strcmp(name, "grow_colmaker3")) return new ColMaker< CVGradStats<3> >();
  utils::Error("unknown updater:%s", name);
  return NULL;
}
