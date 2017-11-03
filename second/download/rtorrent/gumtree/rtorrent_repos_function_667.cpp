unsigned int
WindowDownloadTransferList::rows() const {
  if (m_canvas->width() < 18)
    return 0;

//   return (m_download->download()->chunks_total() + chunks_per_row() - 1) / chunks_per_row();
  return 0;
}