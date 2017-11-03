void
HttpQueue::erase(iterator itr) {
  m_signalErase.emit(*itr);

  delete *itr;
  Base::erase(itr);
}