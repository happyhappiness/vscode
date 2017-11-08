int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  cur_data = Data;
  cur_size = Size;
  wrote = 0;
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, open_sock);
  curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, set_opt);
#if defined(FUZZER_FTP)
  curl_easy_setopt(curl, CURLOPT_URL, "ftp://user@localhost/file.txt");
#elif defined(FUZZER_IMAP)
  curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");
  curl_easy_setopt(curl, CURLOPT_URL, "imap://localhost");
#elif defined(FUZZER_POP3)
  curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");
  curl_easy_setopt(curl, CURLOPT_URL, "pop3://localhost");
#elif defined(FUZZER_HTTP_UPLOAD)
  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/");
  curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
#elif defined(FUZZER_HTTP2)
  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/");
  /* use non-TLS HTTP/2 without HTTP/1.1 Upgrade: */
  curl_easy_setopt(curl, CURLOPT_HTTP_VERSION,
                   CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE);
#else
  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/");
  curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
#endif
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  close(server_fd);
  close(client_fd);
  server_fd = -1;
  client_fd = -1;
  cur_data = NULL;
  cur_size = -1;
  return 0;
}