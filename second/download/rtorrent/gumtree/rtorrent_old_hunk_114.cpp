    throw torrent::internal_error("print_ddmmyyyy(...) failed.");

  return print_buffer(first, last, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year));
}

char*
print_download_title(char* first, char* last, core::Download* d) {
  return print_buffer(first, last, " %s", d->get_download().name().c_str());
}

char*
print_download_info(char* first, char* last, core::Download* d) {
  first = print_buffer(first, last, "Torrent: ");

  if (!d->get_download().is_open())
    first = print_buffer(first, last, "closed            ");

  else if (d->is_done())
    first = print_buffer(first, last, "done %10.1f MB", (double)d->get_download().bytes_total() / (double)(1 << 20));
  else
    first = print_buffer(first, last, "%6.1f / %6.1f MB",
		       (double)d->get_download().bytes_done() / (double)(1 << 20),
		       (double)d->get_download().bytes_total() / (double)(1 << 20));
  
  first = print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
		     (double)d->get_download().up_rate()->rate() / (1 << 10),
		     (double)d->get_download().down_rate()->rate() / (1 << 10),
		     (double)d->get_download().up_rate()->total() / (1 << 20));

  if (d->get_download().is_active() && !d->is_done()) {
    first = print_buffer(first, last, " ");
    first = print_download_percentage_done(first, last, d);

    first = print_buffer(first, last, " ");
    first = print_download_time_left(first, last, d);
  } else {
