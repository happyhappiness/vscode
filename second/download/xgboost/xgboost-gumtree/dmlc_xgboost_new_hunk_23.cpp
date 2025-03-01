/*!
 * Copyright 2014 by Contributors
 * \file learner.cc
 * \brief Implementation of learning algorithm.
 * \author Tianqi Chen
 */
#include <xgboost/learner.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <limits>
#include "./common/io.h"
#include "./common/random.h"

namespace xgboost {
// implementation of base learner.
bool Learner::AllowLazyCheckPoint() const {
  return gbm_->AllowLazyCheckPoint();
}

std::vector<std::string>
Learner::Dump2Text(const FeatureMap& fmap, int option) const {
  return gbm_->Dump2Text(fmap, option);
}

// simple routine to convert any data to string
template<typename T>
inline std::string ToString(const T& data) {
  std::ostringstream os;
  os << data;
  return os.str();
}

/*! \brief training parameter for regression */
struct LearnerModelParam
    : public dmlc::Parameter<LearnerModelParam> {
  /* \brief global bias */
  float base_score;
  /* \brief number of features  */
  unsigned num_feature;
  /* \brief number of classes, if it is multi-class classification  */
  int num_class;
  /*! \brief reserved field */
  int reserved[31];
  /*! \brief constructor */
  LearnerModelParam() {
    std::memset(this, 0, sizeof(LearnerModelParam));
    base_score = 0.5f;
  }
  // declare parameters
  DMLC_DECLARE_PARAMETER(LearnerModelParam) {
    DMLC_DECLARE_FIELD(base_score).set_default(0.5f)
        .describe("Global bias of the model.");
    DMLC_DECLARE_FIELD(num_feature).set_default(0)
        .describe("Number of features in training data,"\
                  " this parameter will be automatically detected by learner.");
    DMLC_DECLARE_FIELD(num_class).set_default(0).set_lower_bound(0)
        .describe("Number of class option for multi-class classifier. "\
                  " By default equals 0 and corresponds to binary classifier.");
  }
};


struct LearnerTrainParam
    : public dmlc::Parameter<LearnerTrainParam> {
  // stored random seed
  int seed;
  // whether seed the PRNG each iteration
  bool seed_per_iteration;
  // data split mode, can be row, col, or none.
  int dsplit;
  // internal test flag
  std::string test_flag;
  // maximum buffered row value
  float prob_buffer_row;
  // declare parameters
  DMLC_DECLARE_PARAMETER(LearnerTrainParam) {
    DMLC_DECLARE_FIELD(seed).set_default(0)
        .describe("Random number seed during training.");
    DMLC_DECLARE_FIELD(seed_per_iteration).set_default(false)
        .describe("Seed PRNG determnisticly via iterator number, "\
                  "this option will be switched on automatically on distributed mode.");
    DMLC_DECLARE_FIELD(dsplit).set_default(0)
        .add_enum("auto", 0)
        .add_enum("col", 1)
        .add_enum("row", 2)
        .describe("Data split mode for distributed trainig. ");
    DMLC_DECLARE_FIELD(test_flag).set_default("")
        .describe("Internal test flag");
    DMLC_DECLARE_FIELD(prob_buffer_row).set_default(1.0f).set_range(0.0f, 1.0f)
        .describe("Maximum buffered row portion");
  }
};

/*!
 * \brief learner that performs gradient boosting for a specific objective function.
 *  It does training and prediction.
 */
class LearnerImpl : public Learner {
 public:
  explicit LearnerImpl(const std::vector<DMatrix*>& cache_mats)
      noexcept(false) {
    // setup the cache setting in constructor.
    CHECK_EQ(cache_.size(), 0);
    size_t buffer_size = 0;
    for (auto it  = cache_mats.begin(); it != cache_mats.end(); ++it) {
      // avoid duplication.
      if (std::find(cache_mats.begin(), it, *it) != it) continue;
      DMatrix* pmat = *it;
      pmat->cache_learner_ptr_ = this;
      cache_.push_back(CacheEntry(pmat, buffer_size, pmat->info().num_row));
      buffer_size += pmat->info().num_row;
    }
    pred_buffer_size_ = buffer_size;
    // boosted tree
    name_obj_ = "reg:linear";
    name_gbm_ = "gbtree";
  }

  void Configure(const std::vector<std::pair<std::string, std::string> >& args) override {
    tparam.InitAllowUnknown(args);
    // add to configurations
    cfg_.clear();
    for (const auto& kv : args) {
      if (kv.first == "eval_metric") {
        // check duplication
        auto dup_check = [&kv](const std::unique_ptr<Metric>&m) {
          return m->Name() != kv.second;
        };
        if (std::all_of(metrics_.begin(), metrics_.end(), dup_check)) {
          metrics_.emplace_back(Metric::Create(kv.second));
        }
      } else {
        cfg_[kv.first] = kv.second;
      }
    }
    // add additional parameter
    // These are cosntraints that need to be satisfied.
    if (tparam.dsplit == 0 && rabit::IsDistributed()) {
      tparam.dsplit = 2;
    }

    if (cfg_.count("num_class") != 0) {
      cfg_["num_output_group"] = cfg_["num_class"];
    }

    if (cfg_.count("max_delta_step") == 0 &&
        cfg_.count("objective") != 0 &&
        cfg_["objective"] == "count:poisson") {
      cfg_["max_delta_step"] = "0.7";
    }

    if (cfg_.count("updater") == 0) {
      if (tparam.dsplit == 1) {
        cfg_["updater"] = "distcol";
      } else if (tparam.dsplit == 2) {
        cfg_["updater"] = "grow_histmaker,prune";
      }
      if (tparam.prob_buffer_row != 1.0f) {
        cfg_["updater"] = "grow_histmaker,refresh,prune";
      }
    }
    if (cfg_.count("objective") == 0) {
      cfg_["objective"] = "reg:linear";
    }
    if (cfg_.count("booster") == 0) {
      cfg_["booster"] = "gbtree";
    }

    if (!this->ModelInitialized()) {
      mparam.InitAllowUnknown(args);
      name_obj_ = cfg_["objective"];
      name_gbm_ = cfg_["booster"];
    }

    common::GlobalRandom().seed(tparam.seed);

    // set number of features correctly.
    cfg_["num_feature"] = ToString(mparam.num_feature);
    if (gbm_.get() != nullptr) {
      gbm_->Configure(cfg_.begin(), cfg_.end());
    }
    if (obj_.get() != nullptr) {
      obj_->Configure(cfg_.begin(), cfg_.end());
    }
  }

  void Load(dmlc::Stream* fi) override {
    // TODO(tqchen) mark deprecation of old format.
    common::PeekableInStream fp(fi);
    // backward compatible header check.
    std::string header;
    header.resize(4);
    if (fp.PeekRead(&header[0], 4) == 4) {
      CHECK_NE(header, "bs64")
          << "Base64 format is no longer supported in brick.";
      if (header == "binf") {
        CHECK_EQ(fp.Read(&header[0], 4), 4);
      }
    }
    // use the peekable reader.
    fi = &fp;
    std::string name_gbm, name_obj;
    // read parameter
    CHECK_EQ(fi->Read(&mparam, sizeof(mparam)), sizeof(mparam))
        << "BoostLearner: wrong model format";
    {
      // backward compatibility code for compatible with old model type
      // for new model, Read(&name_obj_) is suffice
      uint64_t len;
      CHECK_EQ(fi->Read(&len, sizeof(len)), sizeof(len));
      if (len >= std::numeric_limits<unsigned>::max()) {
        int gap;
        CHECK_EQ(fi->Read(&gap, sizeof(gap)), sizeof(gap))
            << "BoostLearner: wrong model format";
        len = len >> static_cast<uint64_t>(32UL);
      }
      if (len != 0) {
        name_obj.resize(len);
        CHECK_EQ(fi->Read(&name_obj_[0], len), len)
            <<"BoostLearner: wrong model format";
      }
    }
    CHECK(fi->Read(&name_gbm_))
        << "BoostLearner: wrong model format";
    // duplicated code with LazyInitModel
    obj_.reset(ObjFunction::Create(cfg_.at(name_obj_)));
    gbm_.reset(GradientBooster::Create(cfg_.at(name_gbm_)));
    if (metrics_.size() == 0) {
      metrics_.emplace_back(Metric::Create(obj_->DefaultEvalMetric()));
    }
    this->base_score_ = mparam.base_score;
    gbm_->ResetPredBuffer(pred_buffer_size_);
    cfg_["num_class"] = ToString(mparam.num_class);
    obj_->Configure(cfg_.begin(), cfg_.end());
  }

  // rabit save model to rabit checkpoint
  void Save(dmlc::Stream *fo) const override {
    fo->Write(&mparam, sizeof(LearnerModelParam));
    fo->Write(name_obj_);
    fo->Write(name_gbm_);
    gbm_->Save(fo);
  }

  void UpdateOneIter(int iter, DMatrix* train) override {
    if (tparam.seed_per_iteration || rabit::IsDistributed()) {
      common::GlobalRandom().seed(tparam.seed * kRandSeedMagic + iter);
    }
    this->LazyInitDMatrix(train);
    this->LazyInitModel();
    this->PredictRaw(train, &preds_);
    obj_->GetGradient(preds_, train->info(), iter, &gpair_);
    gbm_->DoBoost(train, this->FindBufferOffset(train), &gpair_);
  }

  void BoostOneIter(int iter,
                    DMatrix* train,
                    std::vector<bst_gpair>* in_gpair) override {
    if (tparam.seed_per_iteration || rabit::IsDistributed()) {
      common::GlobalRandom().seed(tparam.seed * kRandSeedMagic + iter);
    }
    gbm_->DoBoost(train, this->FindBufferOffset(train), in_gpair);
  }

  std::string EvalOneIter(int iter,
                          const std::vector<DMatrix*>& data_sets,
                          const std::vector<std::string>& data_names) override {
    std::ostringstream os;
    os << '[' << iter << ']';
    for (size_t i = 0; i < data_sets.size(); ++i) {
      this->PredictRaw(data_sets[i], &preds_);
      obj_->EvalTransform(&preds_);
      for (auto& ev : metrics_) {
        os << '\t' << data_names[i] << '-' << ev->Name() << ':'
           << ev->Eval(preds_, data_sets[i]->info(), tparam.dsplit == 2);
      }
    }
    return os.str();
  }

  std::pair<std::string, float> Evaluate(DMatrix* data, std::string metric) {
    if (metric == "auto") metric = obj_->DefaultEvalMetric();
    std::unique_ptr<Metric> ev(Metric::Create(metric.c_str()));
    this->PredictRaw(data, &preds_);
    obj_->EvalTransform(&preds_);
    return std::make_pair(metric, ev->Eval(preds_, data->info(), tparam.dsplit == 2));
  }

  void Predict(DMatrix* data,
               bool output_margin,
               std::vector<float> *out_preds,
               unsigned ntree_limit,
               bool pred_leaf) const override {
    if (pred_leaf) {
      gbm_->PredictLeaf(data, out_preds, ntree_limit);
    } else {
      this->PredictRaw(data, out_preds, ntree_limit);
      if (!output_margin) {
        obj_->PredTransform(out_preds);
      }
    }
  }

 protected:
  // check if p_train is ready to used by training.
  // if not, initialize the column access.
  inline void LazyInitDMatrix(DMatrix *p_train) {
    if (p_train->HaveColAccess()) return;
    int ncol = static_cast<int>(p_train->info().num_col);
    std::vector<bool> enabled(ncol, true);
    // set max row per batch to limited value
    // in distributed mode, use safe choice otherwise
    size_t max_row_perbatch = std::numeric_limits<size_t>::max();
    if (tparam.test_flag == "block" || tparam.dsplit == 2) {
      max_row_perbatch = 32UL << 10UL;
    }
    // initialize column access
    p_train->InitColAccess(enabled,
                           tparam.prob_buffer_row,
                           max_row_perbatch);
    if (!p_train->SingleColBlock() && cfg_.count("updater") == 0) {
      cfg_["updater"] = "grow_histmaker,prune";
      if (gbm_.get() != nullptr) {
        gbm_->Configure(cfg_.begin(), cfg_.end());
      }
    }
  }

  // return whether model is already initialized.
  inline bool ModelInitialized() const {
    return gbm_.get() != nullptr;
  }
  // lazily initialize the model if it haven't yet been initialized.
  inline void LazyInitModel() {
    if (this->ModelInitialized()) return;
    // estimate feature bound
    unsigned num_feature = 0;
    for (size_t i = 0; i < cache_.size(); ++i) {
      num_feature = std::max(num_feature,
                             static_cast<unsigned>(cache_[i].mat_->info().num_col));
    }
    // run allreduce on num_feature to find the maximum value
    rabit::Allreduce<rabit::op::Max>(&num_feature, 1);
    if (num_feature > mparam.num_feature) {
      mparam.num_feature = num_feature;
    }
    // reset the base score
    mparam.base_score = obj_->ProbToMargin(mparam.base_score);

    // setup
    cfg_["num_feature"] = ToString(mparam.num_feature);
    CHECK(obj_.get() == nullptr && gbm_.get() == nullptr);
    obj_.reset(ObjFunction::Create(name_obj_));
    gbm_.reset(GradientBooster::Create(name_gbm_));
    gbm_->Configure(cfg_.begin(), cfg_.end());
    obj_->Configure(cfg_.begin(), cfg_.end());
    if (metrics_.size() == 0) {
      metrics_.emplace_back(Metric::Create(obj_->DefaultEvalMetric()));
    }
    this->base_score_ = mparam.base_score;
    gbm_->ResetPredBuffer(pred_buffer_size_);
  }
  /*!
   * \brief get un-transformed prediction
