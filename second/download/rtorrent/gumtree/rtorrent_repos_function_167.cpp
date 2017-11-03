torrent::Object
get_variable_d_fn_t::operator () (core::Download* download, const torrent::Object& arg1) {
  if (m_firstKey == NULL)
    return download->bencode()->get_key(m_secondKey);
  else
    return download->bencode()->get_key(m_firstKey).get_key(m_secondKey);
}