void
Manager::adjust_layout() {
  Canvas::redraw_std();
  m_rootFrame.balance(0, 0, Canvas::get_screen_width(), Canvas::get_screen_height());

  schedule_update(0);
}