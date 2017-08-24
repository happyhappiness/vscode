{
        /* In Windows 2000 SEC_I_CONTEXT_EXPIRED (close_notify) is not
           returned so we have to work around that in cleanup. */
        connssl->recv_sspi_close_notify = true;
        if(!connssl->recv_connection_closed) {
          connssl->recv_connection_closed = true;
          infof(data, "schannel: server closed the connection\n");
        }
        goto cleanup;
      }