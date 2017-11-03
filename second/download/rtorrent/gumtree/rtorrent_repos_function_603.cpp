void
Window::set_active(bool state) {
  if (state == is_active())
    return;

  if (state) {
    // Set offscreen so we don't try rendering before Frame::balance
    // has been called.
    m_flags |= flag_active | flag_offscreen;
    mark_dirty();

  } else {
    m_flags &= ~flag_active;
    m_slotUnschedule(this);
  }
}