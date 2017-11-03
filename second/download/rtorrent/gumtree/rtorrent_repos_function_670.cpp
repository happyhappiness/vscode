int
WindowFileList::done_percentage(torrent::File* e) {
  int chunks = e->range().second - e->range().first;

  return chunks ? (e->completed_chunks() * 100) / chunks : 100;
}