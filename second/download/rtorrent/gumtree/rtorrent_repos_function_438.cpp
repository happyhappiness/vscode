unsigned int
CurlStack::fdset(fd_set* readfds, fd_set* writefds, fd_set* exceptfds) {
  int maxFd = 0;

  if (curl_multi_fdset((CURLM*)m_handle, readfds, writefds, exceptfds, &maxFd) != 0)
    throw torrent::internal_error("Error calling curl_multi_fdset.");

  return std::max(maxFd, 0);
}