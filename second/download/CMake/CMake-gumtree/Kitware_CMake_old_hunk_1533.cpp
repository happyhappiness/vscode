    {

      if (k != -1)

        errno = EINVAL;

      return -1;

    }



    /* write block to output file */

    if (write(fdout, buf,

        ((i > T_BLOCKSIZE) ? T_BLOCKSIZE : i)) == -1)

      return -1;

  }



  /* close output file */

  if (close(fdout) == -1)

    return -1;



#ifdef DEBUG

  printf("### done extracting %s\n", filename);

