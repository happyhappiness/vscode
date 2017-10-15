char*
print_download_status(char* first, char* last, core::Download* d) {
  if (d->is_active())
    ;
  else if (rpc::call_command_value("d.hashing", rpc::make_target(d)) != 0)
    first = print_buffer(first, last, "Hashing: ");
  else if (!d->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
                         (d->download()->chunks_hashed() * 100) / d->download()->file_list()->size_chunks());

  } else if (d->tracker_list()->has_active() && d->tracker_list()->focus() < d->tracker_list()->end()) {
    torrent::TrackerList* tl = d->tracker_list();
    char status[128];

    (*tl->focus())->get_status(status, sizeof(status));
    first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s %s",
                         (*tl->focus())->group(), tl->focus_index(), (*tl->focus())->url().c_str(), status);

  } else if (!d->message().empty()) {
    first = print_buffer(first, last, "%s", d->message().c_str());

  } else {
    *first = '\0';
  }

  if (first > last)
    throw torrent::internal_error("print_download_status(...) wrote past end of the buffer.");

  return first;
}