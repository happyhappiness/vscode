{  /* initialize version flags when version wraps around */
      version = INIT_ATTS_VERSION;
      for (j = nsAttsSize; j != 0; )
        nsAtts[--j].version = version;
    }