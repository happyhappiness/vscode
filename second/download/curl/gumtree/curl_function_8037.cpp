CURLcode Curl_ssl_push_certinfo_len(struct SessionHandle *data,
                                    int certnum,
                                    const char *label,
                                    const char *value,
                                    size_t valuelen)
{
  struct curl_certinfo * ci = &data->info.certs;
  char * output;
  struct curl_slist * nl;
  CURLcode res = CURLE_OK;

  /* Add an information record for a particular certificate. */
  output = curl_maprintf("%s:%.*s", label, valuelen, value);
  if(!output)
    return CURLE_OUT_OF_MEMORY;

  nl = Curl_slist_append_nodup(ci->certinfo[certnum], output);
  if(!nl) {
    free(output);
    curl_slist_free_all(ci->certinfo[certnum]);
    res = CURLE_OUT_OF_MEMORY;
  }

  ci->certinfo[certnum] = nl;
  return res;
}