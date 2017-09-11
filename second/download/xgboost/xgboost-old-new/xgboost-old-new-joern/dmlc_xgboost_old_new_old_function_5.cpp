inline void SetParam(const char *name, const char *val) {
    using namespace std;
    // in this version, bst: prefix is no longer required
    if (strncmp(name, "bst:", 4) != 0) {
      std::string n = "bst:"; n += name;
      this->SetParam(n.c_str(), val);
    }
    if (!strcmp(name, "silent")) silent = atoi(val);
    if (!strcmp(name, "dsplit")) {
      if (!strcmp(val, "col")) {
        this->SetParam("updater", "distcol");
        distributed_mode = 1;
      } else if (!strcmp(val, "row")) {
        this->SetParam("updater", "grow_histmaker,prune");
        distributed_mode = 2;
      } else {
        utils::Error("%s is invalid value for dsplit, should be row or col", val);
      }
    }
    if (!strcmp(name, "updater_mode")) updater_mode = atoi(val);
    if (!strcmp(name, "prob_buffer_row")) {
      prob_buffer_row = static_cast<float>(atof(val));
      utils::Check(distributed_mode == 0,
                   "prob_buffer_row can only be used in single node mode so far");
      this->SetParam("updater", "grow_colmaker,refresh,prune");
    }
    if (!strcmp(name, "eval_metric")) evaluator_.AddEval(val);
    if (!strcmp("seed", name)) {
      seed = atoi(val); random::Seed(seed);
    }
    if (!strcmp("seed_per_iter", name)) seed_per_iteration = atoi(val);
    if (!strcmp("save_base64", name)) save_base64 = atoi(val);
    if (!strcmp(name, "num_class")) {
      this->SetParam("num_output_group", val);
    }
    if (!strcmp(name, "nthread")) {
      omp_set_num_threads(atoi(val));
    }
    if (gbm_ == NULL) {
      if (!strcmp(name, "objective")) name_obj_ = val;
      if (!strcmp(name, "booster")) name_gbm_ = val;
      mparam.SetParam(name, val);
    }
    if (gbm_ != NULL) gbm_->SetParam(name, val);
    if (obj_ != NULL) obj_->SetParam(name, val);
    if (gbm_ == NULL || obj_ == NULL) {
      cfg_.push_back(std::make_pair(std::string(name), std::string(val)));
    }
  }