      return CURLE_FTP_WEIRD_227_FORMAT;
    }

    snprintf(newhost, sizeof(newhost),
             "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    newhostp = newhost;
    newport = (port[0]<<8) + port[1];
  }
  else if (229 == results[modeoff]) {
    char *ptr = strchr(buf, '(');
    if(ptr) {
