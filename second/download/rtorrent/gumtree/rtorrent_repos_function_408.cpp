PollManagerEPoll*
PollManagerEPoll::create(int maxOpenSockets) {
  torrent::PollEPoll* p = torrent::PollEPoll::create(maxOpenSockets);

  if (p == NULL)
    return NULL;
  else
    return new PollManagerEPoll(p);
}