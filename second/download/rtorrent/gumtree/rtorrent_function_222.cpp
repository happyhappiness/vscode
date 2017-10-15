void
apply_close_low_diskspace(Control* m, int64_t arg) {
  core::Manager::DListItr itr = m->core()->download_list()->begin();

  while ((itr = std::find_if(itr, m->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != m->core()->download_list()->end()) {
    rak::fs_stat stat;
    std::string path = (*itr)->file_list()->root_dir() + (*itr)->file_list()->get(0).path()->as_string();

    if (!stat.update(path)) {
      m->core()->push_log(std::string("Cannot read free diskspace: ") + strerror(errno) + " for " + path);

    } else if (stat.bytes_avail() < arg) {
      m->core()->download_list()->close(*itr);

      (*itr)->set_hash_failed(true);
      (*itr)->set_message(std::string("Low diskspace"));
    }

    ++itr;
  }
}