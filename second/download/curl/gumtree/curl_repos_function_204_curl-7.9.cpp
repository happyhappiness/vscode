CURLcode Curl_ftp_disconnect(struct connectdata *conn)
{
  struct FTP *ftp= conn->proto.ftp;

  /* The FTP session may or may not have been allocated/setup at this point! */
  if(ftp) {
    if(ftp->entrypath)
      free(ftp->entrypath);
  }
  return CURLE_OK;
}