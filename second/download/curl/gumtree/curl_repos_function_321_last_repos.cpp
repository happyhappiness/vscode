int
Curl_gsk_attribute_get_numeric_value(gsk_handle my_gsk_handle,
                                     GSK_NUM_ID numID, int * numValue)

{
  struct Curl_gsk_descriptor * p;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  return gsk_attribute_get_numeric_value(p->h, numID, numValue);
}