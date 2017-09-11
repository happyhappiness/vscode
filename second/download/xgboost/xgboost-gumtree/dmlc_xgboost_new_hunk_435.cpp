/*! \brief implementation of sync goes to here */
class SyncManager {  
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
    this->host_uri = utils::SockAddr::GetHostName();
    // get information from master
    utils::TCPSocket master;
    master.Create();
    master.Connect(utils::SockAddr(master_uri.c_str(), master_port));
    utils::Assert(master.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 1");
    utils::Assert(master.RecvAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 2");
    utils::Check(magic == kMagic, "sync::Invalid master message, init failure");
    utils::Assert(master.RecvAll(&rank, sizeof(rank)) == sizeof(rank), "sync::Init failure 3");
    utils::Assert(master.RecvAll(&world_size, sizeof(world_size)) == sizeof(world_size), "sync::Init failure 4");
    utils::Assert(master.RecvAll(&nparent, sizeof(nparent)) == sizeof(nparent), "sync::Init failure 5");
    utils::Assert(master.RecvAll(&nchild, sizeof(nchild)) == sizeof(nchild), "sync::Init failure 6");
    utils::Assert(nchild >= 0, "in correct number of childs");
    utils::Assert(nparent == 1 || nparent == 0, "in correct number of parent");

    // create listen
    utils::TCPSocket sock_listen;
    sock_listen.Create();
    int port = sock_listen.TryBindHost(slave_port, slave_port + nport_trial);
    utils::Check(port != -1, "sync::Init fail to bind the ports specified");
    sock_listen.Listen();

    if (nparent != 0) {
      parent_index = 0;
      links.push_back(LinkRecord());
      int len, hport;
      std::string hname;
      utils::Assert(master.RecvAll(&len, sizeof(len)) == sizeof(len), "sync::Init failure 9");
      hname.resize(len);
      utils::Assert(len != 0, "string must not be empty");
      utils::Assert(master.RecvAll(&hname[0], len) == static_cast<size_t>(len), "sync::Init failure 10");
      utils::Assert(master.RecvAll(&hport, sizeof(hport)) == sizeof(hport), "sync::Init failure 11");
      links[0].sock.Create();
      links[0].sock.Connect(utils::SockAddr(hname.c_str(), hport));
      utils::Assert(links[0].sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
      utils::Assert(links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
      utils::Check(magic == kMagic, "sync::Init failure, parent magic number mismatch");
      parent_index = 0;
    } else {
      parent_index = -1;
    }
    // send back socket listening port to master
    utils::Assert(master.SendAll(&port, sizeof(port)) == sizeof(port), "sync::Init failure 12");
    // close connection to master
    master.Close();
    // accept links from childs
    for (int i = 0; i < nchild; ++i) {
      LinkRecord r; 
      while (true) {
        r.sock = sock_listen.Accept();
        if (links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic) && magic == kMagic) {
          utils::Assert(r.sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure");
          break;
        } else {
          // not a valid child
          r.sock.Close();
        }
      }
      links.push_back(r);
    }
    // close listening sockets
    sock_listen.Close();
    // setup selecter
    selecter.Clear();
    for (size_t i = 0; i < links.size(); ++i) {
      selecter.WatchRead(links[i].sock);
      selecter.WatchWrite(links[i].sock);
    }
    // done
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
  }
  /*! \brief get rank */
  inline int GetRank(void) const {
    return rank;
  }  
  /*! \brief get rank */
  inline int GetWorldSize(void) const {
    return world_size;
  }
  /*! \brief get rank */
  inline std::string GetHost(void) const {
    return host_uri;
  }
  /*!
   * \brief perform in-place allreduce, on sendrecvbuf 
