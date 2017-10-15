    throw torrent::internal_error("print_ddmmyyyy(...) failed.");

  return print_buffer(first, last, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year));
}

char*
print_address(char* first, char* last, const rak::socket_address* sa) {
  if (!sa->address_c_str(first, last - first))
    return first;

  return std::find(first, last, '\0');
}

inline char*
print_address(char* first, char* last, const sockaddr* sa) {
  return print_address(first, last, rak::socket_address::cast_from(sa));
}

char*
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
