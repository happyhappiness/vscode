 public:
  const static int kMagic = 0xff99;
  SyncManager(void) {
    master_uri = "localhost";
    master_port = 9000;
    slave_port = 9010;
    nport_trial = 1000;
  }
  ~SyncManager(void) {
    this->Shutdown();
  }
  // initialize the manager
  inline void Init(void) {
    utils::Assert(links.size() == 0, "can only call Init once");
    int magic = kMagic;
    int nchild = 0, nparent = 0;
