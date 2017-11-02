int
curl_formget_ccsid(struct curl_httppost * form, void * arg,
                   curl_formget_callback append, unsigned int ccsid)

{
  cfcdata lcfc;

  lcfc.append = append;
  lcfc.arg = arg;
  lcfc.ccsid = ccsid;
  return curl_formget(form, (void *) &lcfc, Curl_formget_callback_ccsid);
}