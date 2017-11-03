CommandScheduler::iterator
CommandScheduler::insert(const std::string& key) {
  if (key.empty())
    throw torrent::input_error("Scheduler received an empty key.");

  iterator itr = find(key);

  if (itr == end())
    itr = base_type::insert(end(), NULL);
  else
    delete *itr;

  *itr = new CommandSchedulerItem(key);
  (*itr)->set_slot(rak::bind_mem_fn(this, &CommandScheduler::call_item, *itr));

  return itr;
}