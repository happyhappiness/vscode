torrent::Object
set_variable_d_fn_t::operator () (core::Download* download, const torrent::Object& arg1) {
  if (m_firstKey == NULL)
    download->bencode()->get_key(m_secondKey) = arg1;
  else
    download->bencode()->get_key(m_firstKey).get_key(m_secondKey) = arg1;

  return torrent::Object();
}