  }

  if (d->priority() != 2)
    first = print_buffer(first, last, " [%s]", core::Download::priority_to_string(d->priority()));

  if (first > last)
    throw torrent::client_error("print_download_info(...) wrote past end of the buffer.");

  return first;
}

char*
print_download_status(char* first, char* last, core::Download* d) {
  if (!d->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
		       (d->download()->chunks_hashed() * 100) / d->download()->chunks_total());

  } else if (d->tracker_list()->is_busy() && d->tracker_list()->focus() < d->tracker_list()->size()) {
    torrent::TrackerList* tl = d->tracker_list();

