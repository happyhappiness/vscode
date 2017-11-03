void
Control::set_umask(mode_t m) {
  ::umask(m);

  m_umask = m;
}