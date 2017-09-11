/*!
 * Copyright by Contributors
 * \file gbtree-inl.hpp
 * \brief gradient boosted tree implementation
 * \author Tianqi Chen
 */
#ifndef XGBOOST_GBM_GBTREE_INL_HPP_
#define XGBOOST_GBM_GBTREE_INL_HPP_

#include <vector>
#include <utility>
#include <string>
#include <limits>
#include "./gbm.h"
#include "../utils/omp.h"
#include "../tree/updater.h"

namespace xgboost {
namespace gbm {
/*!
 * \brief gradient boosted tree
 */
class GBTree : public IGradBooster {
 public:
  GBTree(void) {
  }
  virtual ~GBTree(void) {
    this->Clear();
  }
  virtual void SetParam(const char *name, const char *val) {
    using namespace std;
    if (!strncmp(name, "bst:", 4)) {
      cfg.push_back(std::make_pair(std::string(name+4), std::string(val)));
      // set into updaters, if already initialized
      for (size_t i = 0; i < updaters.size(); ++i) {
        updaters[i]->SetParam(name+4, val);
      }
    }
    if (!strcmp(name, "silent")) {
      this->SetParam("bst:silent", val);
    }
    tparam.SetParam(name, val);
    if (trees.size() == 0) mparam.SetParam(name, val);
  }
  virtual void LoadModel(utils::IStream &fi, bool with_pbuffer) { // NOLINT(*)
    this->Clear();
    utils::Check(fi.Read(&mparam, sizeof(ModelParam)) != 0,
                 "GBTree: invalid model file");
    trees.resize(mparam.num_trees);
    for (size_t i = 0; i < trees.size(); ++i) {
      trees[i] = new tree::RegTree();
      trees[i]->LoadModel(fi);
    }
    tree_info.resize(mparam.num_trees);
    if (mparam.num_trees != 0) {
      utils::Check(fi.Read(&tree_info[0], sizeof(int) * mparam.num_trees) != 0,
                   "GBTree: invalid model file");
    }
    if (mparam.num_pbuffer != 0 && with_pbuffer) {
      pred_buffer.resize(mparam.PredBufferSize());
      pred_counter.resize(mparam.PredBufferSize());
      utils::Check(fi.Read(&pred_buffer[0], pred_buffer.size() * sizeof(float)) != 0,
                   "GBTree: invalid model file");
      utils::Check(fi.Read(&pred_counter[0], pred_counter.size() * sizeof(unsigned)) != 0,
                   "GBTree: invalid model file");
    }
  }
  virtual void SaveModel(utils::IStream &fo, bool with_pbuffer) const { // NOLINT(*)
    utils::Assert(mparam.num_trees == static_cast<int>(trees.size()), "GBTree");
    if (with_pbuffer) {
      fo.Write(&mparam, sizeof(ModelParam));
    } else {
      ModelParam p = mparam;
      p.num_pbuffer = 0;
      fo.Write(&p, sizeof(ModelParam));
    }
    for (size_t i = 0; i < trees.size(); ++i) {
      trees[i]->SaveModel(fo);
    }
    if (tree_info.size() != 0) {
      fo.Write(BeginPtr(tree_info), sizeof(int) * tree_info.size());
    }
    if (mparam.num_pbuffer != 0 && with_pbuffer) {
      fo.Write(BeginPtr(pred_buffer), pred_buffer.size() * sizeof(float));
      fo.Write(BeginPtr(pred_counter), pred_counter.size() * sizeof(unsigned));
    }
  }
  // initialize the predict buffer
  virtual void InitModel(void) {
    pred_buffer.clear(); pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
    utils::Assert(mparam.num_trees == 0, "GBTree: model already initialized");
    utils::Assert(trees.size() == 0, "GBTree: model already initialized");
  }
  virtual void ResetPredBuffer(size_t num_pbuffer) {
    mparam.num_pbuffer = static_cast<int64_t>(num_pbuffer);
    pred_buffer.clear(); pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
  }
  virtual bool AllowLazyCheckPoint(void) const {
    return !(tparam.distcol_mode != 0  && mparam.num_output_group != 1);
  }
  virtual void DoBoost(IFMatrix *p_fmat,
                       int64_t buffer_offset,
                       const BoosterInfo &info,
                       std::vector<bst_gpair> *in_gpair) {
    const std::vector<bst_gpair> &gpair = *in_gpair;
    std::vector<std::vector<tree::RegTree*> > new_trees;
    if (mparam.num_output_group == 1) {
      new_trees.push_back(BoostNewTrees(gpair, p_fmat, buffer_offset, info, 0));
    } else {
      const int ngroup = mparam.num_output_group;
      utils::Check(gpair.size() % ngroup == 0,
                   "must have exactly ngroup*nrow gpairs");
      std::vector<bst_gpair> tmp(gpair.size()/ngroup);
      for (int gid = 0; gid < ngroup; ++gid) {
        bst_omp_uint nsize = static_cast<bst_omp_uint>(tmp.size());
        #pragma omp parallel for schedule(static)
        for (bst_omp_uint i = 0; i < nsize; ++i) {
          tmp[i] = gpair[i * ngroup + gid];
        }
        new_trees.push_back(BoostNewTrees(tmp, p_fmat, buffer_offset, info, gid));
      }
    }
    for (int gid = 0; gid < mparam.num_output_group; ++gid) {
      this->CommitModel(new_trees[gid], gid);
    }
  }
  virtual void Predict(IFMatrix *p_fmat,
                       int64_t buffer_offset,
                       const BoosterInfo &info,
                       std::vector<float> *out_preds,
                       unsigned ntree_limit = 0) {
    int nthread;
    #pragma omp parallel
    {
      nthread = omp_get_num_threads();
    }
    InitThreadTemp(nthread);
    std::vector<float> &preds = *out_preds;
    const size_t stride = info.num_row * mparam.num_output_group;
    preds.resize(stride * (mparam.size_leaf_vector+1));
    // start collecting the prediction
    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
    iter->BeforeFirst();
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
