void
Manager::erase(Bindings* b) {
  iterator itr = std::find(begin(), end(), b);

  if (itr == end())
    return;

  Base::erase(itr);

  if (std::find(begin(), end(), b) != end())
    throw torrent::internal_error("Manager::erase(...) found duplicate bindings.");
}