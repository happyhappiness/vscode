void
Curl_sec_end(struct connectdata *conn)
{
  if (conn->mech != NULL) {
    if(conn->mech->end)
      (conn->mech->end)(conn->app_data);
    memset(conn->app_data, 0, conn->mech->size);
    free(conn->app_data);
    conn->app_data = NULL;
  }
  conn->sec_complete = 0;
  conn->data_prot = (enum protection_level)0;
  conn->mech=NULL;
}