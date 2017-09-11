/*!
 * Copyright 2014 by Contributors
 * \file gbtree.cc
 * \brief gradient boosted tree implementation.
 * \author Tianqi Chen
 */
#include <dmlc/logging.h>
#include <dmlc/omp.h>
#include <dmlc/parameter.h>
#include <xgboost/gbm.h>
#include <xgboost/tree_updater.h>

#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <limits>

namespace xgboost {
namespace gbm {

/*! \brief training parameters */
struct GBTreeTrainParam : public dmlc::Parameter<GBTreeTrainParam> {
  /*! \brief number of threads */
  int nthread;
  /*!
   * \brief number of parallel trees constructed each iteration
   *  use this option to support boosted random forest
   */
  int num_parallel_tree;
  /*! \brief tree updater sequence */
  std::string updater_seq;
  // declare parameters
  DMLC_DECLARE_PARAMETER(GBTreeTrainParam) {
    DMLC_DECLARE_FIELD(nthread).set_lower_bound(0).set_default(0)
        .describe("Number of threads used for training.");
    DMLC_DECLARE_FIELD(num_parallel_tree).set_lower_bound(1).set_default(1)
        .describe("Number of parallel trees constructed during each iteration."\
                  " This option is used to support boosted random forest");
    DMLC_DECLARE_FIELD(updater_seq).set_default("grow_colmaker,prune")
        .describe("Tree updater sequence.");
  }
};

/*! \brief model parameters */
struct GBTreeModelParam : public dmlc::Parameter<GBTreeModelParam> {
  /*! \brief number of trees */
  int num_trees;
  /*! \brief number of roots */
  int num_roots;
  /*! \brief number of features to be used by trees */
  int num_feature;
  /*! \brief pad this space, for backward compatiblity reason.*/
  int pad_32bit;
  /*! \brief size of prediction buffer allocated used for buffering */
  int64_t num_pbuffer;
  /*!
   * \brief how many output group a single instance can produce
   *  this affects the behavior of number of output we have:
   *    suppose we have n instance and k group, output will be k * n
   */
  int num_output_group;
  /*! \brief size of leaf vector needed in tree */
  int size_leaf_vector;
  /*! \brief reserved parameters */
  int reserved[32];
  /*! \brief constructor */
  GBTreeModelParam() {
    std::memset(this, 0, sizeof(GBTreeModelParam));
    static_assert(sizeof(GBTreeModelParam) == (4 + 2 + 2 + 32) * sizeof(int),
                  "64/32 bit compatibility issue");
  }
  // declare parameters, only declare those that need to be set.
  DMLC_DECLARE_PARAMETER(GBTreeModelParam) {
    DMLC_DECLARE_FIELD(num_output_group).set_lower_bound(1).set_default(1)
        .describe("Number of output groups to be predicted,"\
                  " used for multi-class classification.");
    DMLC_DECLARE_FIELD(num_roots).set_lower_bound(1).set_default(1)
        .describe("Tree updater sequence.");
    DMLC_DECLARE_FIELD(num_feature).set_lower_bound(0)
        .describe("Number of features used for training and prediction.");
    DMLC_DECLARE_FIELD(size_leaf_vector).set_lower_bound(0).set_default(0)
        .describe("Reserved option for vector tree.");
  }
  /*! \return size of prediction buffer actually needed */
  inline size_t PredBufferSize() const {
    return num_output_group * num_pbuffer * (size_leaf_vector + 1);
  }
  /*!
   * \brief get the buffer offset given a buffer index and group id
   * \return calculated buffer offset
   */
  inline int64_t BufferOffset(int64_t buffer_index, int bst_group) const {
    if (buffer_index < 0) return -1;
    CHECK_LT(buffer_index, num_pbuffer);
    return (buffer_index + num_pbuffer * bst_group) * (size_leaf_vector + 1);
  }
};

// gradient boosted trees
class GBTree : public GradientBooster {
 public:
  void Configure(const std::vector<std::pair<std::string, std::string> >& cfg) override {
    this->cfg = cfg;
    // initialize model parameters if not yet been initialized.
    if (trees.size() == 0) {
      mparam.InitAllowUnknown(cfg);
    }
    // initialize the updaters only when needed.
    std::string updater_seq = tparam.updater_seq;
    tparam.InitAllowUnknown(cfg);
    if (updater_seq != tparam.updater_seq) updaters.clear();
    for (const auto& up : updaters) {
      up->Init(cfg);
    }
  }
  void LoadModel(dmlc::Stream* fi) override {
    CHECK_EQ(fi->Read(&mparam, sizeof(mparam)), sizeof(mparam))
        << "GBTree: invalid model file";
    trees.clear();
    for (int i = 0; i < mparam.num_trees; ++i) {
      std::unique_ptr<RegTree> ptr(new RegTree());
      ptr->LoadModel(fi);
      trees.push_back(std::move(ptr));
    }
    tree_info.resize(mparam.num_trees);
    if (mparam.num_trees != 0) {
      CHECK_EQ(fi->Read(dmlc::BeginPtr(tree_info), sizeof(int) * mparam.num_trees),
               sizeof(int) * mparam.num_trees);
    }
    this->ResetPredBuffer(0);
  }
  void SaveModel(dmlc::Stream* fo) const override {
    CHECK_EQ(mparam.num_trees, static_cast<int>(trees.size()));
    // not save predict buffer.
    GBTreeModelParam p = mparam;
    p.num_pbuffer = 0;
    fo->Write(&p, sizeof(p));
    for (size_t i = 0; i < trees.size(); ++i) {
      trees[i]->SaveModel(fo);
    }
    if (tree_info.size() != 0) {
      fo->Write(dmlc::BeginPtr(tree_info), sizeof(int) * tree_info.size());
    }
  }
  void InitModel() override {
    CHECK(mparam.num_trees == 0 && trees.size() == 0)
        << "Model has already been initialized.";
    pred_buffer.clear();
    pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
  }
  void ResetPredBuffer(size_t num_pbuffer) override {
    mparam.num_pbuffer = static_cast<int64_t>(num_pbuffer);
    pred_buffer.clear();
    pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
  }
  bool AllowLazyCheckPoint() const override {
    return mparam.num_output_group == 1 ||
        tparam.updater_seq.find("distcol") != std::string::npos;
  }
  void DoBoost(DMatrix* p_fmat,
               int64_t buffer_offset,
               std::vector<bst_gpair>* in_gpair) override {
    const std::vector<bst_gpair>& gpair = *in_gpair;
    std::vector<std::vector<std::unique_ptr<RegTree> > > new_trees;
    if (mparam.num_output_group == 1) {
      std::vector<std::unique_ptr<RegTree> > ret;
      BoostNewTrees(gpair, p_fmat, buffer_offset, 0, &ret);
      new_trees.push_back(std::move(ret));
    } else {
      const int ngroup = mparam.num_output_group;
      CHECK_EQ(gpair.size() % ngroup, 0)
          << "must have exactly ngroup*nrow gpairs";
      std::vector<bst_gpair> tmp(gpair.size() / ngroup);
      for (int gid = 0; gid < ngroup; ++gid) {
        bst_omp_uint nsize = static_cast<bst_omp_uint>(tmp.size());
        #pragma omp parallel for schedule(static)
        for (bst_omp_uint i = 0; i < nsize; ++i) {
          tmp[i] = gpair[i * ngroup + gid];
        }
        std::vector<std::unique_ptr<RegTree> > ret;
        BoostNewTrees(tmp, p_fmat, buffer_offset, gid, &ret);
        new_trees.push_back(std::move(ret));
      }
    }
    for (int gid = 0; gid < mparam.num_output_group; ++gid) {
      this->CommitModel(std::move(new_trees[gid]), gid);
    }
  }
  void Predict(DMatrix* p_fmat,
               int64_t buffer_offset,
               std::vector<float>* out_preds,
               unsigned ntree_limit) override {
    const MetaInfo& info = p_fmat->info();
    int nthread;
    #pragma omp parallel
    {
      nthread = omp_get_num_threads();
    }
    InitThreadTemp(nthread);
    std::vector<float> &preds = *out_preds;
    const size_t stride = p_fmat->info().num_row * mparam.num_output_group;
    preds.resize(stride * (mparam.size_leaf_vector+1));
    // start collecting the prediction
    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();

    iter->BeforeFirst();
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
