void
ViewManager::set_filter_on(const std::string& name, const filter_args& args) {
  iterator viewItr = find_throw(name);

  (*viewItr)->clear_filter_on();

  for (filter_args::const_iterator itr = args.begin(); itr != args.end(); ++itr) {

    if (*itr == "start")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_START);

    else if (*itr == "stop")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_STOP);

    else if (*itr == "hash_queued")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_HASH_QUEUED);

    else if (*itr == "hash_removed")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_HASH_REMOVED);

    else if (*itr == "hash_done")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_HASH_DONE);

    else if (*itr == "finished")
      (*viewItr)->set_filter_on(DownloadList::SLOTS_FINISHED);

    else
      throw torrent::input_error("Invalid filter on identifier.");

  }
}