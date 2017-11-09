int fuzz_initialize_fuzz_data(FUZZ_DATA *fuzz,
                              const uint8_t *data,
                              size_t data_len)
{
  int rc = 0;

  /* Initialize the fuzz data. */
  memset(fuzz, 0, sizeof(FUZZ_DATA));

  /* Create an easy handle. This will have all of the settings configured on
     it. */
  fuzz->easy = curl_easy_init();
  FCHECK(fuzz->easy != NULL);

  /* Set some standard options on the CURL easy handle. We need to override the
     socket function so that we create our own sockets to present to CURL. */
  FTRY(curl_easy_setopt(fuzz->easy,
                        CURLOPT_OPENSOCKETFUNCTION,
                        fuzz_open_socket));
  FTRY(curl_easy_setopt(fuzz->easy, CURLOPT_OPENSOCKETDATA, fuzz));

  /* In case something tries to set a socket option, intercept this. */
  FTRY(curl_easy_setopt(fuzz->easy,
                        CURLOPT_SOCKOPTFUNCTION,
                        fuzz_sockopt_callback));

  /* Set the standard read function callback. */
  FTRY(curl_easy_setopt(fuzz->easy,
                        CURLOPT_READFUNCTION,
                        fuzz_read_callback));
  FTRY(curl_easy_setopt(fuzz->easy, CURLOPT_READDATA, fuzz));

  /* Set the standard write function callback. */
  FTRY(curl_easy_setopt(fuzz->easy,
                        CURLOPT_WRITEFUNCTION,
                        fuzz_write_callback));
  FTRY(curl_easy_setopt(fuzz->easy, CURLOPT_WRITEDATA, fuzz));

  /* Can enable verbose mode by changing 0L to 1L */
  FTRY(curl_easy_setopt(fuzz->easy, CURLOPT_VERBOSE, 0L));

  /* Set up the state parser */
  fuzz->state.data = data;
  fuzz->state.data_len = data_len;

EXIT_LABEL:

  return rc;
}