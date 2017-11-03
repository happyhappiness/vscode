void
CurlStack::remove_get(CurlGet* get) {
  iterator itr = std::find(begin(), end(), get);

  if (itr == end())
    throw torrent::internal_error("Could not find CurlGet when calling CurlStack::remove.");

  base_type::erase(itr);

  // The CurlGet object was never activated, so we just skip this one.
  if (!get->is_active())
    return;

  get->set_active(false);

  if (curl_multi_remove_handle((CURLM*)m_handle, get->handle()) > 0)
    throw torrent::internal_error("Error calling curl_multi_remove_handle.");

  if (m_active == m_maxActive &&
      (itr = std::find_if(begin(), end(), std::not1(std::mem_fun(&CurlGet::is_active)))) != end()) {
    (*itr)->set_active(true);

    if (curl_multi_add_handle((CURLM*)m_handle, (*itr)->handle()) > 0)
      throw torrent::internal_error("Error calling curl_multi_add_handle.");

  } else {
    m_active--;
  }
}