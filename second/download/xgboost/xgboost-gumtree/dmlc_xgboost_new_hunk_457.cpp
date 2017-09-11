  if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
  if (!strcmp(name, "grow_qhistmaker")) return new QuantileHistMaker<GradStats>();
  if (!strcmp(name, "grow_cqmaker")) return new CQHistMaker<GradStats>();
  if (!strcmp(name, "distcol")) return new DistColMaker<GradStats>();

  utils::Error("unknown updater:%s", name);
  return NULL;
}
