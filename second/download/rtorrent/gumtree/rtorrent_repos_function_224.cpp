CommandScheduler::iterator
CommandScheduler::find(const std::string& key) {
  return std::find_if(begin(), end(), rak::equal(key, std::mem_fun(&CommandSchedulerItem::key)));
}