void AllreduceBase::Init(void) {
  // setup from enviroment variables
  // handler to get variables from env
  for (size_t i = 0; i < env_vars.size(); ++i) {
    const char *value = getenv(env_vars[i].c_str());
    if (value != NULL) {
      this->SetParam(env_vars[i].c_str(), value);
    }
  }
  {
    // handling for hadoop
    const char *task_id = getenv("mapred_tip_id");
    if (task_id == NULL) {
      task_id = getenv("mapreduce_task_id");
    }
    if (hadoop_mode != 0) {
      utils::Check(task_id != NULL,
                   "hadoop_mode is set but cannot find mapred_task_id");
    }
    if (task_id != NULL) {
      this->SetParam("rabit_task_id", task_id);
      this->SetParam("rabit_hadoop_mode", "1");
    }
    const char *attempt_id = getenv("mapred_task_id");
    if (attempt_id != 0) {
      const char *att = strrchr(attempt_id, '_');
      int num_trial;
      if (att != NULL && sscanf(att + 1, "%d", &num_trial) == 1) {
        this->SetParam("rabit_num_trial", att + 1);
      }
    }
    // handling for hadoop
    const char *num_task = getenv("mapred_map_tasks");
    if (num_task == NULL) {
      num_task = getenv("mapreduce_job_maps");
    }
    if (hadoop_mode != 0) {
      utils::Check(num_task != NULL,
                   "hadoop_mode is set but cannot find mapred_map_tasks");
    }
    if (num_task != NULL) {
      this->SetParam("rabit_world_size", num_task);
    }
  }
  if (dmlc_role != "worker") {
    fprintf(stderr, "Rabit Module currently only work with dmlc worker, quit this program by exit 0\n");
    exit(0);
  }
  // clear the setting before start reconnection
  this->rank = -1;
  //---------------------
  // start socket
  utils::Socket::Startup();
  utils::Assert(all_links.size() == 0, "can only call Init once");
  this->host_uri = utils::SockAddr::GetHostName();
  // get information from tracker
  this->ReConnectLinks();
}