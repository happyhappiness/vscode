void Curl_ssl_sessionid_unlock(struct connectdata *conn)
{
  if(SSLSESSION_SHARED(conn->data))
    Curl_share_unlock(conn->data, CURL_LOCK_DATA_SSL_SESSION);
}