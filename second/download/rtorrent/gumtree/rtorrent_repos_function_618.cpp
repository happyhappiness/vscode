unsigned int
WindowDownloadChunksSeen::rows() const {
  if (m_canvas->width() < 18)
    return 0;

  return (m_download->download()->file_list()->size_chunks() + chunks_per_row() - 1) / chunks_per_row();
}