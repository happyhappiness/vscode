bool
PathInput::pressed(int key) {
  // Consider binding tab in m_bindings instead.

  if (key != '\t') {
    m_showNext = false;
    return TextInput::pressed(key);

  } else if (m_showNext) {
    m_signalShowNext.emit();

  } else {
    receive_do_complete();
  }

  return true;
}