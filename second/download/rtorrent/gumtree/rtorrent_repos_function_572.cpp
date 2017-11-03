void
Manager::set_hashing_view(View* v) {
  if (v == NULL || m_hashingView != NULL)
    throw torrent::internal_error("Manager::set_hashing_view(...) received NULL or is already set.");

  m_hashingView = v;
  v->signal_changed().connect(sigc::mem_fun(this, &Manager::receive_hashing_changed));
}