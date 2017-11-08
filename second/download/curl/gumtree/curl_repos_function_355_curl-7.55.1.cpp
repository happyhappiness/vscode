struct curl_slist *
curl_slist_append_ccsid(struct curl_slist * list,
                        const char * data, unsigned int ccsid)

{
  char * s;

  s = (char *) NULL;

  if(!data)
    return curl_slist_append(list, data);

  s = dynconvert(ASCII_CCSID, data, -1, ccsid);

  if(!s)
    return (struct curl_slist *) NULL;

  list = curl_slist_append(list, s);
  free(s);
  return list;
}