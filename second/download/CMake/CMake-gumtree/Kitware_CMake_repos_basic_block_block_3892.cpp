{
    conn->proto.generic = NULL;
    RTMP_Close(r);
    RTMP_Free(r);
  }