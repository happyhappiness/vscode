void
SCgi::event_error() {
  throw torrent::internal_error("SCGI listener port received an error event.");
}