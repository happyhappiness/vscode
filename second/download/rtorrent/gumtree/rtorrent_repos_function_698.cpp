void
Frame::balance(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  m_positionX = x;
  m_positionY = y;
  m_width = width;
  m_height = height;

  switch (m_type) {
  case TYPE_NONE:   break;
  case TYPE_WINDOW: balance_window(x, y, width, height); break;
  case TYPE_ROW:    balance_row(x, y, width, height); break;
  case TYPE_COLUMN: balance_column(x, y, width, height); break;
  }
}