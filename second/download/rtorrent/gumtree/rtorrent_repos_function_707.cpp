void
Manager::receive_update() {
  if (m_forceRedraw) {
    m_forceRedraw = false;

    display::Canvas::resize_term(display::Canvas::term_size());
    Canvas::redraw_std();

    adjust_layout();
    m_rootFrame.redraw();
  }

  Canvas::refresh_std();

  rak::priority_queue_perform(&m_scheduler, cachedTime);
  m_rootFrame.refresh();

  Canvas::do_update();

  m_timeLastUpdate = cachedTime;
  schedule_update(50000);
}