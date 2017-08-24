f(conn->port < 0)
    /* we check for -1 here since if proxy was detected already, this
       was very likely already set to the proxy port */
    conn->port = p->defport