HttpQueue::iterator
HttpQueue::insert(const std::string& url, std::iostream* s) {
  std::auto_ptr<CurlGet> h(m_slotFactory());
  
  h->set_url(url);
  h->set_stream(s);

  iterator itr = Base::insert(end(), h.get());

  h->signal_done().connect(sigc::bind(sigc::mem_fun(this, &HttpQueue::erase), itr));
  h->signal_failed().connect(sigc::bind<0>(sigc::hide(sigc::mem_fun(this, &HttpQueue::erase)), itr));

  (*itr)->start();

  h.release();
  m_signalInsert.emit(*itr);

  return itr;
}