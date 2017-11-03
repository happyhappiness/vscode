void
InputEvent::insert(torrent::Poll* p) {
  p->open(this);
  p->insert_read(this);
}