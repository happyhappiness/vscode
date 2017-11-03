void
DownloadStore::remove(Download* d) {
  if (!is_enabled())
    return;

  ::unlink(create_filename(d).c_str());
}