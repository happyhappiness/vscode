void
View::sort() {
  Download* curFocus = focus() != end_visible() ? *focus() : NULL;

  // Don't go randomly switching around equivalent elements.
  std::stable_sort(begin(), end_visible(), view_downloads_compare(m_sortCurrent));

  m_focus = position(std::find(begin(), end_visible(), curFocus));
  m_signalChanged.emit();
}