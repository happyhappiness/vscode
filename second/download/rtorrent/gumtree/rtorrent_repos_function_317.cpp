void
Root::setup_keys() {
  m_control->input()->push_back(&m_bindings);

  const std::string& keyLayout = rpc::call_command_string("get_key_layout");

  if (strcasecmp(keyLayout.c_str(), "azerty") == 0) {
    m_bindings['q']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 1);
    m_bindings['w']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -1);
    m_bindings['Q']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 1);
    m_bindings['W']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -1);

  } else if (strcasecmp(keyLayout.c_str(), "qwertz") == 0) {
    m_bindings['a']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 1);
    m_bindings['y']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -1);
    m_bindings['A']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 1);
    m_bindings['Y']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -1);

  } else if (strcasecmp(keyLayout.c_str(), "dvorak") == 0) {
    m_bindings['a']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 1);
    m_bindings[';']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -1);
    m_bindings['A']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 1);
    m_bindings[':']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -1);

  } else {
    m_bindings['a']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 1);
    m_bindings['z']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -1);
    m_bindings['A']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 1);
    m_bindings['Z']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -1);
  }

  if (strcasecmp(keyLayout.c_str(), "dvorak") != 0) {
    m_bindings['s']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 5);
    m_bindings['x']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -5);
    m_bindings['S']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 5);
    m_bindings['X']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -5);

    m_bindings['d']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 50);
    m_bindings['c']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -50);
    m_bindings['D']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 50);
    m_bindings['C']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -50);

  } else {
    m_bindings['o']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 5);
    m_bindings['q']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -5);
    m_bindings['O']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 5);
    m_bindings['Q']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -5);

    m_bindings['e']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), 50);
    m_bindings['j']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_up_throttle), -50);
    m_bindings['E']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), 50);
    m_bindings['J']           = sigc::bind(sigc::mem_fun(*this, &Root::adjust_down_throttle), -50);
  }

  m_bindings['\x0C']        = sigc::mem_fun(m_control->display(), &display::Manager::force_redraw); // ^L
  m_bindings['\x11']        = sigc::mem_fun(m_control, &Control::receive_normal_shutdown); // ^Q
}