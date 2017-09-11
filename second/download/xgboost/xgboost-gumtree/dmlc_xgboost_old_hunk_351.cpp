  if (!strcmp(name, "prune")) return new TreePruner();
  if (!strcmp(name, "refresh")) return new TreeRefresher<GradStats>();
  if (!strcmp(name, "grow_colmaker")) return new ColMaker<GradStats>();
  utils::Error("unknown updater:%s", name);
  return NULL;
}
