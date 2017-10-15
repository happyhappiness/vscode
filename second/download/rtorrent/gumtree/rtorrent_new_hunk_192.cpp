
void
apply_close_low_diskspace(Control* m, int64_t arg) {
  core::Manager::DListItr itr = m->core()->download_list()->begin();

  while ((itr = std::find_if(itr, m->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != m->core()->download_list()->end()) {
    if ((*itr)->file_list()->free_diskspace() < (uint64_t)arg) {
      m->core()->download_list()->close(*itr);

      (*itr)->set_hash_failed(true);
      (*itr)->set_message(std::string("Low diskspace."));
    }

    ++itr;
  }
}

