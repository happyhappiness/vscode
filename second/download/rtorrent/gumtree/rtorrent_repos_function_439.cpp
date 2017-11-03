void
CurlStack::add_get(CurlGet* get) {
  if (!m_userAgent.empty())
    curl_easy_setopt(get->handle(), CURLOPT_USERAGENT, m_userAgent.c_str());

  if (!m_httpProxy.empty())
    curl_easy_setopt(get->handle(), CURLOPT_PROXY, m_httpProxy.c_str());

  if (!m_bindAddress.empty())
    curl_easy_setopt(get->handle(), CURLOPT_INTERFACE, m_bindAddress.c_str());

  if (!m_httpCaPath.empty())
    curl_easy_setopt(get->handle(), CURLOPT_CAPATH, m_httpCaPath.c_str());

  if (!m_httpCaCert.empty())
    curl_easy_setopt(get->handle(), CURLOPT_CAINFO, m_httpCaCert.c_str());

  base_type::push_back(get);

  if (m_active >= m_maxActive)
    return;

  m_active++;
  get->set_active(true);
  
  if (curl_multi_add_handle((CURLM*)m_handle, get->handle()) > 0)
    throw torrent::internal_error("Error calling curl_multi_add_handle.");
}