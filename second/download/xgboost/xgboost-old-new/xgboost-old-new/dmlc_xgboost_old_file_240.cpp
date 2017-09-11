#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <cstring>
#include "./updater.h"
#include "./updater_sync-inl.hpp"
#include "./updater_prune-inl.hpp"
#include "./updater_refresh-inl.hpp"
#include "./updater_colmaker-inl.hpp"
#include "./updater_distcol-inl.hpp"
#include "./updater_histmaker-inl.hpp"

namespace xgboost {
namespace tree {
IUpdater* CreateUpdater(const char *name) {
  using namespace std;
  if (!strcmp(name, "prune")) return new TreePruner();
  if (!strcmp(name, "sync")) return new TreeSyncher();
  if (!strcmp(name, "refresh")) return new TreeRefresher<GradStats>();
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

}  // namespace tree
}  // namespace xgboost
