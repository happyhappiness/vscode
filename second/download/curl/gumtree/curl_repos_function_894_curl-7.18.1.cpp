static CURLcode ftp_init(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp;
  if(data->state.proto.ftp)
    return CURLE_OK;

  ftp = (struct FTP *)calloc(sizeof(struct FTP), 1);
  if(!ftp)
    return CURLE_OUT_OF_MEMORY;

  data->state.proto.ftp = ftp;

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &data->req.bytecount;

  /* no need to duplicate them, this connectdata struct won't change */
  ftp->user = conn->user;
  ftp->passwd = conn->passwd;
  if(isBadFtpString(ftp->user) || isBadFtpString(ftp->passwd))
    return CURLE_URL_MALFORMAT;

  return CURLE_OK;
}