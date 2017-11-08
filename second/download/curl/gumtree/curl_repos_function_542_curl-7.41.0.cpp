static size_t callback(char* ptr, size_t size, size_t nmemb, void* data)
{
  ssize_t idx = ((CURL **) data) - easy;
  curl_socket_t sock;
  long longdata;
  CURLcode code;

  const size_t failure = (size * nmemb) ? 0 : 1;

  char *output = malloc(size * nmemb + 1);
  if (!output) {
    fprintf(stderr, "output, malloc() failed\n");
    res = TEST_ERR_MAJOR_BAD;
    return failure;
  }

  memcpy(output, ptr, size * nmemb);
  output[size * nmemb] = '\0';
  fprintf(stdout, "%s", output);
  free(output);

  /* Get socket being used for this easy handle, otherwise CURL_SOCKET_BAD */
  code = curl_easy_getinfo(easy[idx], CURLINFO_LASTSOCKET, &longdata);
  if (CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    return failure;
  }
  if (longdata == -1L)
    sock = CURL_SOCKET_BAD;
  else
    sock = (curl_socket_t)longdata;

  if (sock != CURL_SOCKET_BAD) {
    /* Track relationship between this easy handle and the socket. */
    if (sockets[idx] == CURL_SOCKET_BAD) {
      /* An easy handle without previous socket, record the socket. */
      sockets[idx] = sock;
    }
    else if (sock != sockets[idx]) {
      /* An easy handle with a socket different to previously
         tracked one, log and fail right away. Known bug #37. */
      fprintf(stderr, "Handle %d started on socket %d and moved to %d\n",
              curlx_sztosi(idx), (int)sockets[idx], (int)sock);
      res = TEST_ERR_MAJOR_BAD;
      return failure;
    }
  }
  return size * nmemb;
}