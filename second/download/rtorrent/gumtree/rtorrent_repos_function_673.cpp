std::string
WindowHttpQueue::create_name(core::CurlGet* h) {
  size_t p = h->url().rfind('/', h->url().size() - std::min<int>(10, h->url().size()));

  std::string n = p != std::string::npos ? h->url().substr(p) : h->url();

  if (n.empty())
    throw std::logic_error("WindowHttpQueue::create_name(...) made a bad string");

  if (n.size() > 2 && n[0] == '/')
    n = n.substr(1);

  if (n.size() > 9 &&
      (n.substr(n.size() - 8) == ".torrent" ||
       n.substr(n.size() - 8) == ".TORRENT"))
    n = n.substr(0, n.size() - 8);

  if (n.size() > 30)
    n = n.substr(0, 30);

  return n;
}