void
Curl_sec_set_protection_level(struct connectdata *conn)
{
  if(conn->sec_complete && conn->data_prot != conn->request_data_prot)
    sec_prot_internal(conn, conn->request_data_prot);
}