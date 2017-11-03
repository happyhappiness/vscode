void
apply_t_set_enabled(torrent::Tracker* tracker, int64_t state) {
  if (state)
    tracker->enable();
  else
    tracker->disable();
}