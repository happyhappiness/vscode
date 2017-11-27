  status = fprintf (c->fh, "%s\r\n", command);
  if (status < 0)
  {
    lcc_set_errno (c, errno);
    return (-1);
  }
  fflush(c->fh);

  return (0);
} /* }}} int lcc_send */

static int lcc_receive (lcc_connection_t *c, /* {{{ */
    lcc_response_t *ret_res)
