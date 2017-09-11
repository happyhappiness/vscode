      utils::Assert(master.RecvAll(&hname[0], len) == static_cast<size_t>(len), "sync::Init failure 10");
      utils::Assert(master.RecvAll(&hport, sizeof(hport)) == sizeof(hport), "sync::Init failure 11");
      links[0].sock.Create();
      links[0].sock.Connect(utils::SockAddr(hname.c_str(), hport));      
      utils::Assert(links[0].sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 12");
      utils::Assert(links[0].sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 13");
      utils::Check(magic == kMagic, "sync::Init failure, parent magic number mismatch");
      parent_index = 0;
    } else {
      parent_index = -1;
    }
    // send back socket listening port to master
    utils::Assert(master.SendAll(&port, sizeof(port)) == sizeof(port), "sync::Init failure 14");
    // close connection to master
    master.Close();
    // accept links from childs
    for (int i = 0; i < nchild; ++i) {
      LinkRecord r; 
      while (true) {
        r.sock = sock_listen.Accept();
        if (r.sock.RecvAll(&magic, sizeof(magic)) == sizeof(magic) && magic == kMagic) {
          utils::Assert(r.sock.SendAll(&magic, sizeof(magic)) == sizeof(magic), "sync::Init failure 15");
          break;
        } else {         
          // not a valid child
          r.sock.Close();
        }
