r(pp = protocols; (p = *pp) != NULL; pp++) {
    if(strcasecompare(p->scheme, protostr)) {
      /* Protocol found in table. Check if allowed */
      if(!(data->set.allowed_protocols & p->protocol))
        /* nope, get out */
        break;

      /* it is allowed for "normal" request, now do an extra check if this is
         the result of a redirect */
      if(data->state.this_is_a_follow &&
         !(data->set.redir_protocols & p->protocol))
        /* nope, get out */
        break;

      /* Perform setup complement if some. */
      conn->handler = conn->given = p;

      /* 'port' and 'remote_port' are set in setup_connection_internals() */
      return CURLE_OK;
    }
  }