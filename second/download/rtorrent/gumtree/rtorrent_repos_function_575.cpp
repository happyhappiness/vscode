void
Manager::cleanup() {
  // Need to disconnect log signals? Not really since we won't receive
  // any more.

  m_downloadList->clear();

  torrent::cleanup();
  CurlStack::global_cleanup();

  delete m_pollManager;
}