CURLcode Curl_readrewind(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;

  conn->bits.rewindaftersend = FALSE; /* we rewind now */

  /* explicitly switch off sending data on this connection now since we are
     about to restart a new transfer and thus we want to avoid inadvertently
     sending more data on the existing connection until the next transfer
     starts */
  data->req.keepon &= ~KEEP_SEND;

  /* We have sent away data. If not using CURLOPT_POSTFIELDS or
     CURLOPT_HTTPPOST, call app to rewind
  */
  if(data->set.postfields ||
     (data->set.httpreq == HTTPREQ_POST_FORM))
    ; /* do nothing */
  else {
    if(data->set.seek_func) {
      int err;

      err = (data->set.seek_func)(data->set.seek_client, 0, SEEK_SET);
      if(err) {
        failf(data, "seek callback returned error %d", (int)err);
        return CURLE_SEND_FAIL_REWIND;
      }
    }
    else if(data->set.ioctl_func) {
      curlioerr err;

      err = (data->set.ioctl_func)(data, CURLIOCMD_RESTARTREAD,
                                   data->set.ioctl_client);
      infof(data, "the ioctl callback returned %d\n", (int)err);

      if(err) {
        /* FIXME: convert to a human readable error message */
        failf(data, "ioctl callback returned error %d", (int)err);
        return CURLE_SEND_FAIL_REWIND;
      }
    }
    else {
      /* If no CURLOPT_READFUNCTION is used, we know that we operate on a
         given FILE * stream and we can actually attempt to rewind that
         ourselves with fseek() */
      if(data->set.fread_func == (curl_read_callback)fread) {
        if(-1 != fseek(data->set.in, 0, SEEK_SET))
          /* successful rewind */
          return CURLE_OK;
      }

      /* no callback set or failure above, makes us fail at once */
      failf(data, "necessary data rewind wasn't possible");
      return CURLE_SEND_FAIL_REWIND;
    }
  }
  return CURLE_OK;
}