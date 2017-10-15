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
