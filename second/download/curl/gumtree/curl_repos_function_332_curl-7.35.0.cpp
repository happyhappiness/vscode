static struct curl_slist *
slist_convert(int dccsid, struct curl_slist * from, int sccsid)

{
  struct curl_slist * to = (struct curl_slist *) NULL;
  char * cp;

  for(; from; from = from->next) {
    if(!(cp = dynconvert(dccsid, from->data, -1, sccsid))) {
      curl_slist_free_all(to);
      return (struct curl_slist *) NULL;
    }
    to = Curl_slist_append_nodup(to, cp);
  }
  return to;
}