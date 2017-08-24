{
    if(ret != AUTH_OK) {
      /* Mechanism has dumped the error to stderr, don't error here. */
      return -1;
    }
    DEBUGASSERT(ret == AUTH_OK);

    conn->mech = mech;
    conn->sec_complete = 1;
    conn->recv[FIRSTSOCKET] = sec_recv;
    conn->send[FIRSTSOCKET] = sec_send;
    conn->recv[SECONDARYSOCKET] = sec_recv;
    conn->send[SECONDARYSOCKET] = sec_send;
    conn->command_prot = PROT_SAFE;
    /* Set the requested protection level */
    /* BLOCKING */
    (void)sec_set_protection_level(conn);
  }