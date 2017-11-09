static CURLcode ftp_setup_connection(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  char *type;
  char command;
  struct FTP *ftp;

  conn->data->req.protop = ftp = malloc(sizeof(struct FTP));
  if(NULL == ftp)
    return CURLE_OUT_OF_MEMORY;

  data->state.path++;   /* don't include the initial slash */
  data->state.slash_removed = TRUE; /* we've skipped the slash */

  /* FTP URLs support an extension like ";type=<typecode>" that
   * we'll try to get now! */
  type = strstr(data->state.path, ";type=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";type=");

  if(type) {
    *type = 0;                     /* it was in the middle of the hostname */
    command = Curl_raw_toupper(type[6]);
    conn->bits.type_set = TRUE;

    switch(command) {
    case 'A': /* ASCII mode */
      data->set.prefer_ascii = TRUE;
      break;

    case 'D': /* directory mode */
      data->set.ftp_list_only = TRUE;
      break;

    case 'I': /* binary mode */
    default:
      /* switch off ASCII */
      data->set.prefer_ascii = FALSE;
      break;
    }
  }

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &conn->data->req.bytecount;
  ftp->transfer = FTPTRANSFER_BODY;
  ftp->downloadsize = 0;

  /* No need to duplicate user+password, the connectdata struct won't change
     during a session, but we re-init them here since on subsequent inits
     since the conn struct may have changed or been replaced.
  */
  ftp->user = conn->user;
  ftp->passwd = conn->passwd;
  if(isBadFtpString(ftp->user))
    return CURLE_URL_MALFORMAT;
  if(isBadFtpString(ftp->passwd))
    return CURLE_URL_MALFORMAT;

  conn->proto.ftpc.known_filesize = -1; /* unknown size for now */

  return CURLE_OK;
}