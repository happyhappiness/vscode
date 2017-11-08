int test(char *URL)
{
  int res;
  CURL *curl;
  char *stream_uri = NULL;
  int request=1;
  FILE *protofile = NULL;

  protofile = fopen(libtest_arg2, "wb");
  if(protofile == NULL) {
    fprintf(stderr, "Couldn't open the protocol dump file\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    fclose(protofile);
    return TEST_ERR_MAJOR_BAD;
  }

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    fclose(protofile);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }
  test_setopt(curl, CURLOPT_URL, URL);

  if((stream_uri = suburl(URL, request++)) == NULL) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;

  test_setopt(curl, CURLOPT_INTERLEAVEFUNCTION, rtp_write);
  test_setopt(curl, CURLOPT_TIMEOUT, 3L);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);
  test_setopt(curl, CURLOPT_WRITEDATA, protofile);

  test_setopt(curl, CURLOPT_RTSP_TRANSPORT, "RTP/AVP/TCP;interleaved=0-1");
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_SETUP);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  /* This PLAY starts the interleave */
  if((stream_uri = suburl(URL, request++)) == NULL) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_PLAY);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  /* The DESCRIBE request will try to consume data after the Content */
  if((stream_uri = suburl(URL, request++)) == NULL) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_DESCRIBE);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  if((stream_uri = suburl(URL, request++)) == NULL) {
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, stream_uri);
  free(stream_uri);
  stream_uri = NULL;
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_PLAY);

  res = curl_easy_perform(curl);
  if(res)
    goto test_cleanup;

  fprintf(stderr, "PLAY COMPLETE\n");

  /* Use Receive to get the rest of the data */
  while(!res && rtp_packet_count < 13) {
    fprintf(stderr, "LOOPY LOOP!\n");
    test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_RECEIVE);
    res = curl_easy_perform(curl);
  }

test_cleanup:

  if(stream_uri)
    free(stream_uri);

  if(protofile)
    fclose(protofile);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}