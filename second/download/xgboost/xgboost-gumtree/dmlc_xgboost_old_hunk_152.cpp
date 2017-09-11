  // get information from tracker
  utils::TCPSocket tracker;
  tracker.Create();
  if (!tracker.Connect(utils::SockAddr(tracker_uri.c_str(), tracker_port))) {
    utils::Socket::Error("Connect");
  }
  using utils::Assert;
  Assert(tracker.SendAll(&magic, sizeof(magic)) == sizeof(magic),
         "ReConnectLink failure 1");
