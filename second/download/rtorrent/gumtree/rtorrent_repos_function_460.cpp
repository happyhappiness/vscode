DownloadList::iterator
DownloadList::erase(iterator itr) {
  if (itr == end())
    throw torrent::internal_error("DownloadList::erase(...) could not find download.");

  // Makes sure close doesn't restart hashing of this download.
  (*itr)->set_hash_failed(true);

  close(*itr);

  control->core()->download_store()->remove(*itr);

  std::for_each(slot_map_erase().begin(), slot_map_erase().end(), download_list_call(*itr));

  torrent::download_remove(*(*itr)->download());
  delete *itr;

  return base_type::erase(itr);
}