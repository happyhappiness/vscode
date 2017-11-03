Frame::bounds_type
Frame::preferred_size() const {
  switch (m_type) {
  case TYPE_NONE:
    return bounds_type(0, 0, 0, 0);

  case TYPE_WINDOW:
    if (m_window->is_active())
      return bounds_type(m_window->min_width(), m_window->min_height(),
                         m_window->max_width(), m_window->max_height());
    else
      return bounds_type(0, 0, 0, 0);

  case TYPE_ROW:
  case TYPE_COLUMN:
    {
      bounds_type accum(0, 0, 0, 0);

      for (size_type i = 0; i < m_containerSize; ++i) {
        bounds_type p = m_container[i]->preferred_size();
 
        accum.minWidth += p.minWidth;
        accum.minHeight += p.minHeight;

        if (p.maxWidth == Window::extent_full || accum.maxWidth == Window::extent_full)
          accum.maxWidth = Window::extent_full;
        else
          accum.maxWidth += p.maxWidth;

        if (p.maxHeight == Window::extent_full || accum.maxHeight == Window::extent_full)
          accum.maxHeight = Window::extent_full;
        else
          accum.maxHeight += p.maxHeight;
      }

      return accum;
    }
  }

  return bounds_type(0, 0, 0, 0);
}