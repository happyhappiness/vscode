    if(conn->allocptr.host)

      free(conn->allocptr.host);



    if(((conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTPS)) ||

       (!(conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTP)) )

      /* If (HTTPS on port 443) OR (non-HTTPS on port 80) then don't include

         the port number in the host string */

      conn->allocptr.host = aprintf("Host: %s\r\n", host);

    else

      conn->allocptr.host = aprintf("Host: %s:%d\r\n", host,

                                    conn->remote_port);

  }



