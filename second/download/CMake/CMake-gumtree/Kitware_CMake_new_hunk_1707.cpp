

    sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    newhostp = newhost;

    newport = (unsigned short)((port[0]<<8) + port[1]);

  }

#if 1

  else if (229 == results[modeoff]) {

