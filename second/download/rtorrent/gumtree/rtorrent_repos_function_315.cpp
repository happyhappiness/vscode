void
Root::init(Control* c) {
  if (m_control != NULL)
    throw std::logic_error("Root::init() called twice on the same object");

  m_control = c;

  m_windowTitle     = new WTitle();
  m_windowHttpQueue = new WHttpQueue(control->core()->http_queue());
  m_windowInput     = new WInput();
  m_windowStatusbar = new WStatusbar();

  m_downloadList    = new DownloadList();

  display::Frame* rootFrame = m_control->display()->root_frame();

  rootFrame->initialize_row(5);
  rootFrame->frame(0)->initialize_window(m_windowTitle);
  rootFrame->frame(2)->initialize_window(m_windowHttpQueue);
  rootFrame->frame(3)->initialize_window(m_windowInput);
  rootFrame->frame(4)->initialize_window(m_windowStatusbar);

  m_windowTitle->set_active(true);
  m_windowStatusbar->set_active(true);
  m_windowStatusbar->set_bottom(true);

  setup_keys();

  m_downloadList->activate(rootFrame->frame(1));
}