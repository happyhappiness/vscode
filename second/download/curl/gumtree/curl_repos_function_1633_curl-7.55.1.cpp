bool Curl_recv_has_postponed_data(struct connectdata *conn, int sockindex)
{
  struct postponed_data * const psnd = &(conn->postponed[sockindex]);
  return psnd->buffer && psnd->allocated_size &&
         psnd->recv_size > psnd->recv_processed;
}