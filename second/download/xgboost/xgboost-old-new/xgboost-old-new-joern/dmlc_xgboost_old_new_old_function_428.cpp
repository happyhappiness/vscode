e<typename FMatrix>
inline IGradBooster<FMatrix>* CreateGradBooster(const char *name) {
  if (!strcmp("gbtree", name)) return new GBTree<FMatrix>();
  if (!strcmp("gblinear", name)) return new GBLinear<FMatrix>();
  utils::Error("unknown booster type: %s", name);
  return NULL;
}