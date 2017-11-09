static ssize_t get_pre_recved(struct connectdata *conn, int num, char *buf,
                              size_t len)
{
  struct postponed_data * const psnd = &(conn->postponed[num]);
  size_t copysize;
  if(!psnd->buffer)
    return 0;

  DEBUGASSERT(psnd->allocated_size > 0);
  DEBUGASSERT(psnd->recv_size <= psnd->allocated_size);
  DEBUGASSERT(psnd->recv_processed <= psnd->recv_size);
  /* Check and process data that already received and storied in internal
     intermediate buffer */
  if(psnd->recv_size > psnd->recv_processed) {
    DEBUGASSERT(psnd->bindsock == conn->sock[num]);
    copysize = CURLMIN(len, psnd->recv_size - psnd->recv_processed);
    memcpy(buf, psnd->buffer + psnd->recv_processed, copysize);
    psnd->recv_processed += copysize;
  }
  else
    copysize = 0; /* buffer was allocated, but nothing was received */

  /* Free intermediate buffer if it has no unprocessed data */
  if(psnd->recv_processed == psnd->recv_size) {
    free(psnd->buffer);
    psnd->buffer = NULL;
    psnd->allocated_size = 0;
    psnd->recv_size = 0;
    psnd->recv_processed = 0;
#ifdef DEBUGBUILD
    psnd->bindsock = CURL_SOCKET_BAD;
#endif /* DEBUGBUILD */
  }
  return (ssize_t)copysize;
}