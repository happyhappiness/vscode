void
WindowText::clear() {
  std::for_each(begin(), end(), rak::call_delete<TextElement>());
  base_type::clear();
}