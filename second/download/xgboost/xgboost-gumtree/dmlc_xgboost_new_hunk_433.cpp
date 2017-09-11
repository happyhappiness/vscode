 public:
  const static int kMagic = 0xff99;
  SyncManager(void) {
    master_uri = "NULL";
    master_port = 9000;
    host_uri = "";
    slave_port = 9010;
    nport_trial = 1000;
    rank = 0;
    world_size = 1;
    reduce_buffer_size = 128; 
  }
  ~SyncManager(void) {
    this->Shutdown();
  }
  inline void Shutdown(void) {
    for (size_t i = 0; i < links.size(); ++i) {
      links[i].sock.Close();
    }
    links.clear();
  }
  /*! \brief set parameters to the sync manager */
  inline void SetParam(const char *name, const char *val) {
    if (!strcmp(name, "master_uri")) master_uri = val;
    if (!strcmp(name, "master_port")) master_port = atoi(val);
    if (!strcmp(name, "reduce_buffer")) {
      char unit;
      unsigned long amount;
      if (sscanf(val, "%lu%c", &amount, &unit) == 2) {
        switch (unit) {
          case 'B': reduce_buffer_size = amount; break;
          case 'K': reduce_buffer_size = amount << 10UL; break;
          case 'M': reduce_buffer_size = amount << 20UL; break;
          case 'G': reduce_buffer_size = amount << 30UL; break;
          default: utils::Error("invalid format for reduce buffer");
        }
      } else {
        utils::Error("invalid format for reduce_buffer, shhould be {integer}{unit}, unit can be {B, KB, MB, GB}");
      }
    }
  }
  /*! \brief get rank */
  inline int GetRank(void) const {
    return rank;
  }
  /*! \brief check whether its distributed mode */
  inline bool IsDistributed(void) const {
    return links.size() != 0;
  }
  /*! \brief get rank */
  inline int GetWorldSize(void) const {
    return world_size;
  }
  /*! \brief get rank */
  inline std::string GetHost(void) const {
    return host_uri;
  }
  // initialize the manager
  inline void Init(void) {
    // single node mode
    if (master_uri == "NULL") return;
    utils::Assert(links.size() == 0, "can only call Init once");
    int magic = kMagic;
    int nchild = 0, nparent = 0;
