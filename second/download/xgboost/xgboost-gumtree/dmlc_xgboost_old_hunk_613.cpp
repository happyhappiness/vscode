};
}  // namespace gbm
}  // namespace xgboost
#include "gbtree-inl.hpp"
namespace xgboost {
namespace gbm {
template<typename FMatrix>
inline IGradBooster<FMatrix>* CreateGradBooster(const char *name) {
  if (!strcmp("gbtree", name)) return new GBTree<FMatrix>();
  utils::Error("unknown booster type: %s", name);
  return NULL;
}
