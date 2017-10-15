char*
print_download_status(char* first, char* last, core::Download* d) {
  if (!d->get_download().is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->get_download().is_hash_checking())
    first = print_buffer(first, last, "Checking hash [%2i%%]",
		       (d->get_download().chunks_hashed() * 100) / d->get_download().chunks_total());

  else if (d->get_download().is_tracker_busy() &&
	   d->get_download().tracker_focus() < d->get_download().size_trackers())
    first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s",
		       d->get_download().tracker(d->get_download().tracker_focus()).group(),
		       d->get_download().tracker_focus(),
		       d->get_download().tracker(d->get_download().tracker_focus()).url().c_str());

  else if (!d->get_message().empty())
    first = print_buffer(first, last, "%s", d->get_message().c_str());

  else
    *first = '\0';

  if (first > last)
    throw torrent::internal_error("print_download_status(...) wrote past end of the buffer.");

  return first;
}