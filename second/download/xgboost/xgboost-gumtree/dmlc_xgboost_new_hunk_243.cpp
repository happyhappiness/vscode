    if (!strcmp("save_pbuffer", name)) save_with_pbuffer = atoi(val);
    if (!strncmp("eval[", name, 5)) {
      char evname[256];
      utils::Assert(sscanf(name, "eval[%[^]]", evname) == 1,
                    "must specify evaluation name for display");
      eval_data_names.push_back(std::string(evname));
      eval_data_paths.push_back(std::string(val));
    }
    learner.SetParam(name, val);
  }

 public:
  BoostLearnTask(void) {
    // default parameters
