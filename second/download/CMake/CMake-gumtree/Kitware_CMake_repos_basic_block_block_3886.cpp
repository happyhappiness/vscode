{
  RTMP *r = RTMP_Alloc();
  if(!r)
    return CURLE_OUT_OF_MEMORY;

  RTMP_Init(r);
  RTMP_SetBufferMS(r, DEF_BUFTIME);
  if(!RTMP_SetupURL(r, conn->data->change.url)) {
    RTMP_Free(r);
    return CURLE_URL_MALFORMAT;
  }
  conn->proto.generic = r;
  return CURLE_OK;
}