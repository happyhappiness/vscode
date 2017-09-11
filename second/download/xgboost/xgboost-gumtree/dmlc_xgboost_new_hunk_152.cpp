  // get information from tracker
  utils::TCPSocket tracker;
  tracker.Create();

  int retry = 0;
  do {
    fprintf(stderr, "connect to ip: [%s]\n", tracker_uri.c_str());
    if (!tracker.Connect(utils::SockAddr(tracker_uri.c_str(), tracker_port))) {
      if (++retry >= connect_retry) {
        fprintf(stderr, "connect to (failed): [%s]\n", tracker_uri.c_str());
        utils::Socket::Error("Connect");
      } else {
        fprintf(stderr, "retry connect to ip(retry time %d): [%s]\n", retry, tracker_uri.c_str());
        sleep(1);
        continue;
      }
    }
    break;
  } while (1);

  using utils::Assert;
  Assert(tracker.SendAll(&magic, sizeof(magic)) == sizeof(magic),
         "ReConnectLink failure 1");
