void
View::next_focus() {
  if (empty())
    return;

  m_focus = (m_focus + 1) % (size() + 1);

  m_signalChanged.emit();
}