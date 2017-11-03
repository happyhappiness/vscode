bool
Lockfile::try_lock() {
  if (m_path.empty()) {
    m_locked = true;
    return true;
  }

  if (is_stale())
    ::unlink(m_path.c_str());

  // Just do a simple locking for now that isn't safe for network
  // devices.
  int fd = ::open(m_path.c_str(), O_RDWR | O_CREAT | O_EXCL, 0444);

  if (fd == -1)
    return false;

  char buf[256];
  int pos = ::gethostname(buf, 255);

  if (pos == 0) {
    ::snprintf(buf + std::strlen(buf), 255, ":+%i\n", ::getpid());
    ::write(fd, buf, std::strlen(buf));
  }

  ::close(fd);

  m_locked = true;
  return true;
}