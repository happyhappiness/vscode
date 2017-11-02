static void close_one(struct ssl_connect_data *conn,
                      struct SessionHandle *data)
{
  if(conn->handle) {
    gskit_status(data, gsk_secure_soc_close(&conn->handle),
              "gsk_secure_soc_close()", 0);
    conn->handle = (gsk_handle) NULL;
  }
  if(conn->iocport >= 0)
    close_async_handshake(conn);
}