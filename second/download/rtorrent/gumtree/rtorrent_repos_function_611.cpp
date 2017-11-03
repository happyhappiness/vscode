WindowLog::iterator
WindowLog::find_older() {
  return m_log->find_older(cachedTime - rak::timer::from_seconds(60));
}