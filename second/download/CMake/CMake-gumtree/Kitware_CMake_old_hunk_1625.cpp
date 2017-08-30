      return CURLE_FTP_WEIRD_227_FORMAT;

    }



    sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    newhostp = newhost;

    newport = (unsigned short)((port[0]<<8) + port[1]);

  }

#if 1

  else if (229 == results[modeoff]) {

    char *ptr = strchr(buf, '(');

    if(ptr) {

