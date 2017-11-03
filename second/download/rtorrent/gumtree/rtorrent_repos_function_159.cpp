void
SCgi::event_write() {
  throw torrent::internal_error("Listener does not support write().");
}