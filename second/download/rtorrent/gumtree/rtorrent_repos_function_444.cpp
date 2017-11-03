void
CurlGet::start() {
  if (is_busy())
    throw torrent::internal_error("Tried to call CurlGet::start on a busy object.");

  if (m_stream == NULL)
    throw torrent::internal_error("Tried to call CurlGet::start without a valid output stream.");

  m_handle = curl_easy_init();

  curl_easy_setopt(m_handle, CURLOPT_URL,            m_url.c_str());
  curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION,  &curl_get_receive_write);
  curl_easy_setopt(m_handle, CURLOPT_WRITEDATA,      this);

  if (m_timeout != 0) {
    curl_easy_setopt(m_handle, CURLOPT_CONNECTTIMEOUT, 60);
    curl_easy_setopt(m_handle, CURLOPT_TIMEOUT,        m_timeout);
  }

  curl_easy_setopt(m_handle, CURLOPT_FORBID_REUSE,   1);
  curl_easy_setopt(m_handle, CURLOPT_NOSIGNAL,       1);
  curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(m_handle, CURLOPT_MAXREDIRS,      5);
  curl_easy_setopt(m_handle, CURLOPT_IPRESOLVE,      CURL_IPRESOLVE_V4);
  curl_easy_setopt(m_handle, CURLOPT_ENCODING,       "");

  m_stack->add_get(this);
}