inline void InitObjGBM(void) {
    if (obj_ != NULL) return;
    utils::Assert(gbm_ == NULL, "GBM and obj should be NULL");
    obj_ = CreateObjFunction(name_obj_.c_str());
    gbm_ = gbm::CreateGradBooster(name_gbm_.c_str());
    this->InitAdditionDefaultParam();
    // set parameters
    for (size_t i = 0; i < cfg_.size(); ++i) {
      obj_->SetParam(cfg_[i].first.c_str(), cfg_[i].second.c_str());
      gbm_->SetParam(cfg_[i].first.c_str(), cfg_[i].second.c_str());
    }
    if (evaluator_.Size() == 0) {
      evaluator_.AddEval(obj_->DefaultEvalMetric());
    }
  }