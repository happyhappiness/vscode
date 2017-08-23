
    /* we got OK from server */
    if(data->set.ftp_skip_ip) {
      /* told to ignore the remotely given IP but instead use the host we used
         for the control connection */
      infof(data, "Skip %d.%d.%d.%d for data connection, re-use %s instead\n",
            ip[0], ip[1], ip[2], ip[3],
            conn->host.name);
      ftpc->newhost = strdup(control_address(conn));
    }
    else
      ftpc->newhost = aprintf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    if(!ftpc->newhost)
      return CURLE_OUT_OF_MEMORY;

    ftpc->newport = (unsigned short)(((port[0]<<8) + port[1]) & 0xffff);
  }
  else if(ftpc->count1 == 0) {
