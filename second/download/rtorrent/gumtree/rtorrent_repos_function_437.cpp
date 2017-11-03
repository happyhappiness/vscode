void
CurlStack::perform() {
  CURLMcode code;

  do {
    int count;
    code = curl_multi_perform((CURLM*)m_handle, &count);

    if (code > 0)
      throw torrent::internal_error("Error calling curl_multi_perform.");

    if ((unsigned int)count != size()) {
      // Done with some handles.
      int t;
      CURLMsg* msg;

      while ((msg = curl_multi_info_read((CURLM*)m_handle, &t)) != NULL) {
        if (msg->msg != CURLMSG_DONE)
          throw torrent::internal_error("CurlStack::perform() msg->msg != CURLMSG_DONE.");

        iterator itr = std::find_if(begin(), end(), rak::equal(msg->easy_handle, std::mem_fun(&CurlGet::handle)));

        if (itr == end())
          throw torrent::internal_error("Could not find CurlGet with the right easy_handle.");
        
        if (msg->data.result == CURLE_OK)
          (*itr)->signal_done().emit();
        else
          (*itr)->signal_failed().emit(curl_easy_strerror(msg->data.result));
      }
    }

  } while (code == CURLM_CALL_MULTI_PERFORM);
}