  // destrcutor
  virtual ~IGradBooster(void){}
};
}  // namespace gbm
}  // namespace xgboost

#include "gbtree-inl.hpp"
#include "gblinear-inl.hpp"

namespace xgboost {
namespace gbm {
template<typename FMatrix>
inline IGradBooster<FMatrix>* CreateGradBooster(const char *name) {
  if (!strcmp("gbtree", name)) return new GBTree<FMatrix>();
  if (!strcmp("gblinear", name)) return new GBLinear<FMatrix>();
  utils::Error("unknown booster type: %s", name);
  return NULL;
}
}  // namespace gbm
}  // namespace xgboost
#endif  // XGBOOST_GBM_GBM_H_
