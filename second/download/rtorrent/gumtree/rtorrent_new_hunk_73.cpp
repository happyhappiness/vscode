
  m_handle = NULL;
}


double
CurlGet::size_done() {
  double d = 0.0;
  curl_easy_getinfo(m_handle, CURLINFO_SIZE_DOWNLOAD, &d);

  return d;
}

double
CurlGet::size_total() {
  double d = 0.0;
  curl_easy_getinfo(m_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &d);

  return d;
}

void
CurlGet::set_user_agent(const char* s) {
  curl_easy_setopt(m_handle, CURLOPT_USERAGENT, s);
}

void
CurlGet::perform(CURLMsg* msg) {
  if (msg->msg != CURLMSG_DONE)
    throw std::logic_error("CurlGet::process got CURLMSG that isn't done");

  if (msg->data.result == CURLE_OK)
    m_signalDone.emit();
  else
    m_signalFailed.emit(curl_easy_strerror(msg->data.result));
}

}
