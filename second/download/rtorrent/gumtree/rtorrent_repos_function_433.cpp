float
Download::distributed_copies() const {
  const uint8_t* avail = m_download.chunks_seen();
  const uint8_t* end = avail + m_download.file_list()->size_chunks();

  if (avail == NULL)
    return 0;

  int minAvail = std::numeric_limits<uint8_t>::max();
  int num = 0;

  for (; avail < end; ++avail)
    if (*avail == minAvail) {
      num++;
    } else if (*avail < minAvail) {
      minAvail = *avail;
      num = 1;
    }

  return minAvail + 1 - (float)num / m_download.file_list()->size_chunks();
}