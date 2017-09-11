utils::TCPSocket AllreduceBase::ConnectTracker(void) const {
  int magic = kMagic;
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
        #ifdef _MSC_VER
        Sleep(1);
        #else
        sleep(1);
        #endif
        continue;
      }
    }
    break;
  } while (1);

  using utils::Assert;
  Assert(tracker.SendAll(&magic, sizeof(magic)) == sizeof(magic),
         "ReConnectLink failure 1");
  Assert(tracker.RecvAll(&magic, sizeof(magic)) == sizeof(magic),
         "ReConnectLink failure 2");
  utils::Check(magic == kMagic, "sync::Invalid tracker message, init failure");
  Assert(tracker.SendAll(&rank, sizeof(rank)) == sizeof(rank),
                "ReConnectLink failure 3");
  Assert(tracker.SendAll(&world_size, sizeof(world_size)) == sizeof(world_size),
         "ReConnectLink failure 3");
  tracker.SendStr(task_id);
  return tracker;
}