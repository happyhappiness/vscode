void
DownloadStore::save(Download* d) {
  if (!is_enabled())
    return;

  std::fstream f((create_filename(d) + ".new").c_str(), std::ios::out | std::ios::trunc);

  if (!f.is_open())
    return;

  // Move this somewhere else?
  d->bencode()->get_key("rtorrent").insert_key("total_uploaded", d->download()->up_rate()->total());
  d->bencode()->get_key("rtorrent").insert_key("chunks_done", d->download()->file_list()->completed_chunks());

  torrent::Object& resumeObject = d->download()->bencode()->get_key("libtorrent_resume");

  torrent::resume_save_addresses(*d->download(), resumeObject);
  torrent::resume_save_file_priorities(*d->download(), resumeObject);
  torrent::resume_save_tracker_settings(*d->download(), resumeObject);

  f << *d->bencode();

  if (!f.good())
    return;

  f.close();

  // Test the new file, to ensure it is a valid bencode string.
  f.open((create_filename(d) + ".new").c_str(), std::ios::in);

  torrent::Object tmp;
  f >> tmp;

  if (!f.good())
    return;

  f.close();

  ::rename((create_filename(d) + ".new").c_str(), create_filename(d).c_str());
}