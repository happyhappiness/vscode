bool
Lockfile::unlock() {
  m_locked = false;

  if (m_path.empty())
    return true;
  else
    return ::unlink(m_path.c_str()) != -1;
}