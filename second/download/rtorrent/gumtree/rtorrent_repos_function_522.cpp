void
HttpQueue::clear() {
  while (!empty())
    erase(begin());

  Base::clear();
}