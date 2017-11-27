static const char *cdbi_strerror(dbi_conn conn, /* {{{ */
                                 char *buffer, size_t buffer_size) {
  const char *msg;
  int status;

  if (conn == NULL) {
    sstrncpy(buffer, "connection is NULL", buffer_size);
    return buffer;
  }

  msg = NULL;
  status = dbi_conn_error(conn, &msg);
  if ((status >= 0) && (msg != NULL))
    snprintf(buffer, buffer_size, "%s (status %i)", msg, status);
  else
    snprintf(buffer, buffer_size, "dbi_conn_error failed with status %i",
             status);

  return buffer;
}