void Curl_ssl_free_certinfo(struct Curl_easy *data)
{
  int i;
  struct curl_certinfo *ci = &data->info.certs;

  if(ci->num_of_certs) {
    /* free all individual lists used */
    for(i = 0; i<ci->num_of_certs; i++) {
      curl_slist_free_all(ci->certinfo[i]);
      ci->certinfo[i] = NULL;
    }

    free(ci->certinfo); /* free the actual array too */
    ci->certinfo = NULL;
    ci->num_of_certs = 0;
  }
}