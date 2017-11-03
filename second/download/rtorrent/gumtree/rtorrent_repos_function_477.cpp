PollManagerSelect*
PollManagerSelect::create(int maxOpenSockets) {
  torrent::PollSelect* p = torrent::PollSelect::create(maxOpenSockets);

  if (p == NULL)
    return NULL;
  else
    return new PollManagerSelect(p);
}