DownloadList::iterator
DownloadList::insert(Download* download) {
  iterator itr = base_type::insert(end(), download);

  try {
    (*itr)->download()->signal_download_done(sigc::bind(sigc::mem_fun(*this, &DownloadList::received_finished), download));
    (*itr)->download()->signal_hash_done(sigc::bind(sigc::mem_fun(*this, &DownloadList::hash_done), download));

    std::for_each(slot_map_insert().begin(), slot_map_insert().end(), download_list_call(*itr));

  } catch (torrent::local_error& e) {
    // Should perhaps relax this, just print an error and remove the
    // downloads?
    throw torrent::internal_error("Caught during DownloadList::insert(...): " + std::string(e.what()));
  }

  return itr;
}