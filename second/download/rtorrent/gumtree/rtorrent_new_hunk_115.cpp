
  return first;
}

char*
print_download_status(char* first, char* last, core::Download* d) {
  if (!d->download()->is_active())
    first = print_buffer(first, last, "Inactive: ");

  if (d->download()->is_hash_checking()) {
    first = print_buffer(first, last, "Checking hash [%2i%%]",
		       (d->download()->chunks_hashed() * 100) / d->download()->chunks_total());

  } else if (d->tracker_list()->is_busy() && d->tracker_list()->focus() < d->tracker_list()->size()) {
    torrent::TrackerList* tl = d->tracker_list();

    first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s",
			 tl->get(tl->focus()).group(), tl->focus(), tl->get(tl->focus()).url().c_str());

  } else if (!d->message().empty()) {
    first = print_buffer(first, last, "%s", d->message().c_str());

  } else {
    *first = '\0';
  }

  if (first > last)
    throw torrent::internal_error("print_download_status(...) wrote past end of the buffer.");

  return first;
}

char*
print_download_time_left(char* first, char* last, core::Download* d) {
  uint32_t rate = d->download()->down_rate()->rate();

  if (rate < 512)
    return print_buffer(first, last, "--:--:--");
  
  time_t remaining = (d->download()->bytes_total() - d->download()->bytes_done()) / (rate & ~(uint32_t)(512 - 1));

  return print_ddhhmm(first, last, remaining);
}

char*
print_download_percentage_done(char* first, char* last, core::Download* d) {
  if (!d->is_open() || d->is_done())
    //return print_buffer(first, last, "[--%%]");
    return print_buffer(first, last, "     ");
  else
    return print_buffer(first, last, "[%2u%%]", (d->download()->chunks_done() * 100) / d->download()->chunks_total());
}

char*
print_status_info(char* first, char* last) {
  if (torrent::up_throttle() == 0)
    first = print_buffer(first, last, "[Throttle off");
