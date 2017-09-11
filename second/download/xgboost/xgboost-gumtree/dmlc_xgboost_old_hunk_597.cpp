  if (!strcmp(name, "prune")) return new TreePruner<FMatrix>();
  if (!strcmp(name, "refresh")) return new TreeRefresher<FMatrix, GradStats>();
  if (!strcmp(name, "grow_colmaker")) return new ColMaker<FMatrix, GradStats>();
  utils::Error("unknown updater:%s", name);
  return NULL;
}
