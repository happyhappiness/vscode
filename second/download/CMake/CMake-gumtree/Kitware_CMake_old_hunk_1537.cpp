  buf[sizeof(buf)-1] = 0;



  if (mkdirhier(dirname(buf)) == -1)

    return -1;



#ifdef DEBUG

  printf("  ==> extracting: %s (fifo)\n", filename);

