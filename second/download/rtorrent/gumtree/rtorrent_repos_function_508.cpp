void
View::initialize(const std::string& name, core::DownloadList* dlist) {
  if (!m_name.empty())
    throw torrent::internal_error("View::initialize(...) called on an already initialized view.");

  if (name.empty())
    throw torrent::internal_error("View::initialize(...) called with an empty name.");

  std::string key = "0_view_" + name;

  if (dlist->has_slot_insert(key) || dlist->has_slot_erase(key))
    throw torrent::internal_error("View::initialize(...) duplicate key name found in DownloadList.");

  m_name = name;
  m_list = dlist;

  // Urgh, wrong. No filtering being done.
  std::for_each(m_list->begin(), m_list->end(), rak::bind1st(std::mem_fun(&View::push_back), this));

  m_size = base_type::size();
  m_focus = 0;

  m_list->slot_map_insert()[key] = sigc::bind(sigc::mem_fun(this, &View::received), (int)DownloadList::SLOTS_INSERT);
  m_list->slot_map_erase()[key]  = sigc::bind(sigc::mem_fun(this, &View::received), (int)DownloadList::SLOTS_ERASE);

  set_last_changed(rak::timer());
}