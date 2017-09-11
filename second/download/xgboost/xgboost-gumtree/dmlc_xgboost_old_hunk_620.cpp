template<typename FMatrix>
inline IUpdater<FMatrix>* CreateUpdater(const char *name) {
  if (!strcmp(name, "prune")) return new TreePruner<FMatrix>();
  if (!strcmp(name, "grow_colmaker")) return new ColMaker<FMatrix, GradStats>();
  utils::Error("unknown updater:%s", name);
  return NULL;
