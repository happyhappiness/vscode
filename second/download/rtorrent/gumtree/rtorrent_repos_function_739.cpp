void
InputEvent::remove(torrent::Poll* p) {
  p->remove_read(this);
  p->close(this);
}