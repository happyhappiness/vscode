int
Curl_gsk_attribute_set_callback(gsk_handle my_gsk_handle,
                                GSK_CALLBACK_ID callBackID,
                                void * callBackAreaPtr)

{
  struct Curl_gsk_descriptor * p;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  return gsk_attribute_set_callback(p->h, callBackID, callBackAreaPtr);
}