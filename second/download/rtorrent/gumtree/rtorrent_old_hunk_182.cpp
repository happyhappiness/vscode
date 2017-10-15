    first = print_buffer(first, last, "Hashing: ");
  else if (!d->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
                         (d->download()->chunks_hashed() * 100) / d->download()->chunks_total());

  } else if (d->tracker_list()->is_busy() && d->tracker_list()->focus() < d->tracker_list()->size()) {
    torrent::TrackerList* tl = d->tracker_list();

    first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s",
                         tl->get(tl->focus()).group(), tl->focus(), tl->get(tl->focus()).url().c_str());
