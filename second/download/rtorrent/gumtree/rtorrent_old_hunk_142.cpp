print_download_title(char* first, char* last, core::Download* d) {
  return print_buffer(first, last, " %s", d->download()->name().c_str());
}

char*
print_download_info(char* first, char* last, core::Download* d) {
  first = print_buffer(first, last, "Torrent: ");

  if (!d->download()->is_open())
    first = print_buffer(first, last, "closed            ");

  else if (d->is_done())
    first = print_buffer(first, last, "done %10.1f MB", (double)d->download()->bytes_total() / (double)(1 << 20));
  else
    first = print_buffer(first, last, "%6.1f / %6.1f MB",
		       (double)d->download()->bytes_done() / (double)(1 << 20),
		       (double)d->download()->bytes_total() / (double)(1 << 20));
  
  first = print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
		     (double)d->download()->up_rate()->rate() / (1 << 10),
		     (double)d->download()->down_rate()->rate() / (1 << 10),
		     (double)d->download()->up_rate()->total() / (1 << 20));

  if (d->download()->is_active() && !d->is_done()) {
    first = print_buffer(first, last, " ");
    first = print_download_percentage_done(first, last, d);

    first = print_buffer(first, last, " ");
    first = print_download_time_left(first, last, d);
  } else {
    first = print_buffer(first, last, "               ");
  }

  if (d->priority() != 2)
    first = print_buffer(first, last, " [%s]", core::Download::priority_to_string(d->priority()));

  if (first > last)
    throw torrent::client_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}
