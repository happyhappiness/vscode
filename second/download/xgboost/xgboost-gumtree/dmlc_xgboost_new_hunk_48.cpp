/*!
 * Copyright 2014 by Contributors
 * \file updater_basemaker-inl.h
 * \brief implement a common tree constructor
 * \author Tianqi Chen
 */
#ifndef XGBOOST_TREE_UPDATER_BASEMAKER_INL_H_
#define XGBOOST_TREE_UPDATER_BASEMAKER_INL_H_

#include <xgboost/base.h>
#include <xgboost/tree_updater.h>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <utility>
#include "./param.h"
#include "../common/sync.h"
#include "../common/io.h"
#include "../common/random.h"
#include "../common/quantile.h"

namespace xgboost {
namespace tree {
/*!
 * \brief base tree maker class that defines common operation
 *  needed in tree making
 */
class BaseMaker: public TreeUpdater {
 public:
  void Init(const std::vector<std::pair<std::string, std::string> >& args) override {
    param.Init(args);
  }

 protected:
  // helper to collect and query feature meta information
  struct FMetaHelper {
   public:
    /*! \brief find type of each feature, use column format */
    inline void InitByCol(DMatrix* p_fmat,
                          const RegTree& tree) {
      fminmax.resize(tree.param.num_feature * 2);
      std::fill(fminmax.begin(), fminmax.end(),
                -std::numeric_limits<bst_float>::max());
      // start accumulating statistics
      dmlc::DataIter<ColBatch>* iter = p_fmat->ColIterator();
      iter->BeforeFirst();
      while (iter->Next()) {
        const ColBatch& batch = iter->Value();
        for (bst_uint i = 0; i < batch.size; ++i) {
          const bst_uint fid = batch.col_index[i];
          const ColBatch::Inst& c = batch[i];
          if (c.length != 0) {
            fminmax[fid * 2 + 0] = std::max(-c[0].fvalue, fminmax[fid * 2 + 0]);
            fminmax[fid * 2 + 1] = std::max(c[c.length - 1].fvalue, fminmax[fid * 2 + 1]);
          }
        }
      }
      rabit::Allreduce<rabit::op::Max>(dmlc::BeginPtr(fminmax), fminmax.size());
    }
    // get feature type, 0:empty 1:binary 2:real
    inline int Type(bst_uint fid) const {
      CHECK_LT(fid * 2 + 1, fminmax.size())
          << "FeatHelper fid exceed query bound ";
      bst_float a = fminmax[fid * 2];
      bst_float b = fminmax[fid * 2 + 1];
      if (a == -std::numeric_limits<bst_float>::max()) return 0;
