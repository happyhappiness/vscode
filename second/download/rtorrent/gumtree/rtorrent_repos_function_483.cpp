void
DownloadFactory::load() {
  priority_queue_insert(&taskScheduler, &m_taskLoad, cachedTime);
}