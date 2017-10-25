int
Curl_sec_request_prot(struct connectdata *conn, const char *level)
{
  int l = name_to_level(level);
  if(l == -1)
    return -1;
  conn->request_data_prot = (enum protection_level)l;
  return 0;
}