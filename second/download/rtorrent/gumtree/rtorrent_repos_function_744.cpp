void
Manager::pressed(int key) {
  if (m_textInput != NULL)
    m_textInput->pressed(key);
  else
    std::find_if(rbegin(), rend(), std::bind2nd(std::mem_fun(&Bindings::pressed), key));
}