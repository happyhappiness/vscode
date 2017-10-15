  if (d->priority() != 2)
    first = print_buffer(first, last, " %s]", core::Download::priority_to_string(d->priority()));
  else
    first = print_buffer(first, last, "]");

  if (first > last)
    throw torrent::client_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}

char*
print_download_status(char* first, char* last, core::Download* d) {
