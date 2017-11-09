static int server_push_callback(CURL *parent,
                                CURL *easy,
                                size_t num_headers,
                                struct curl_pushheaders *headers,
                                void *userp)
{
  char *headp;
  size_t i;
  int *transfers = (int *)userp;
  char filename[128];
  FILE *out;
  static unsigned int count = 0;

  (void)parent; /* we have no use for this */

  snprintf(filename, 128, "push%u", count++);

  /* here's a new stream, save it in a new file for each new push */
  out = fopen(filename, "wb");

  /* write to this file */
  curl_easy_setopt(easy, CURLOPT_WRITEDATA, out);

  fprintf(stderr, "**** push callback approves stream %u, got %d headers!\n",
          count, (int)num_headers);

  for(i = 0; i<num_headers; i++) {
    headp = curl_pushheader_bynum(headers, i);
    fprintf(stderr, "**** header %u: %s\n", (int)i, headp);
  }

  headp = curl_pushheader_byname(headers, ":path");
  if(headp) {
    fprintf(stderr, "**** The PATH is %s\n", headp /* skip :path + colon */);
  }

  (*transfers)++; /* one more */
  return CURL_PUSH_OK;
}