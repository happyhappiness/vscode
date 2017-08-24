{
        DEBUGASSERT(conn->handler->done);
        /* we ignore the return code for the protocol-specific DONE */
        (void)conn->handler->done(conn, result, FALSE);
        goto out;
      }