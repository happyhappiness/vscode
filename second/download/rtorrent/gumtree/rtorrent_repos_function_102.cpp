void
load_session_torrents(Control* c) {
  // Load session torrents.
  std::list<std::string> l = c->core()->download_store()->get_formated_entries().make_list();

  for (std::list<std::string>::iterator first = l.begin(), last = l.end(); first != last; ++first) {
    core::DownloadFactory* f = new core::DownloadFactory(*first, c->core());

    // Replace with session torrent flag.
    f->set_session(true);
    f->slot_finished(sigc::bind(sigc::ptr_fun(&rak::call_delete_func<core::DownloadFactory>), f));
    f->load();
    f->commit();
  }
}