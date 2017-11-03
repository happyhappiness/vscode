void
DownloadList::setup_keys() {
  m_bindings['\x7f']        = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_LOAD_DEFAULT);
  m_bindings[KEY_BACKSPACE] = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_LOAD_DEFAULT);
  m_bindings['\n']          = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_LOAD_MODIFIED);
  m_bindings[KEY_ENTER]     = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_LOAD_MODIFIED);
  m_bindings['\x0F']        = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_CHANGE_DIRECTORY);
  m_bindings['X' - '@']     = sigc::bind(sigc::mem_fun(*this, &DownloadList::receive_view_input), INPUT_COMMAND);

  m_uiArray[DISPLAY_LOG]->bindings()[KEY_LEFT] =
    m_uiArray[DISPLAY_LOG]->bindings()['B' - '@'] =
    m_uiArray[DISPLAY_LOG]->bindings()[' '] = sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_DOWNLOAD_LIST);

  m_uiArray[DISPLAY_DOWNLOAD_LIST]->bindings()[KEY_RIGHT] =
    m_uiArray[DISPLAY_DOWNLOAD_LIST]->bindings()['F' - '@'] = sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_DOWNLOAD);
  m_uiArray[DISPLAY_DOWNLOAD_LIST]->bindings()['l']       = sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_LOG);
}