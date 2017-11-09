void
curl_certinfo_free_all(struct curl_certinfo *info)

{
  /* Free all memory used by certificate info. */
  if(info) {
    if(info->certinfo) {
      int i;

      for(i = 0; i < info->num_of_certs; i++)
        curl_slist_free_all(info->certinfo[i]);
      free((char *) info->certinfo);
    }
    free((char *) info);
  }
}