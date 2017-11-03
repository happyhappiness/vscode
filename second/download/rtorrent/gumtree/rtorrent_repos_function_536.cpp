PollManagerKQueue*
PollManagerKQueue::create(int maxOpenSockets) {
  torrent::PollKQueue* p = torrent::PollKQueue::create(maxOpenSockets);

  if (p == NULL)
    return NULL;
  else
    return new PollManagerKQueue(p);
}