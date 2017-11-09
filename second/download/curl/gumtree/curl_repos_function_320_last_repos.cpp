int
Curl_gsk_attribute_get_enum(gsk_handle my_gsk_handle, GSK_ENUM_ID enumID,
                            GSK_ENUM_VALUE * enumValue)

{
  struct Curl_gsk_descriptor * p;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  return gsk_attribute_get_enum(p->h, enumID, enumValue);
}