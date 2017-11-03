bool
Bindings::pressed(int key) {
  if (!m_enabled)
    return false;

  const_iterator itr = find(key);

  if (itr == end())
    return false;

  itr->second();
  return true;
}