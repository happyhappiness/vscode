int
Curl_gsk_attribute_get_cert_info(gsk_handle my_gsk_handle,
                                 GSK_CERT_ID certID,
                                 const gsk_cert_data_elem * * certDataElem,
                                 int * certDataElementCount)

{
  struct Curl_gsk_descriptor * p;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  /* No need to convert code: text results are already in ASCII. */
  return gsk_attribute_get_cert_info(p->h, certID,
                                     certDataElem, certDataElementCount);
}