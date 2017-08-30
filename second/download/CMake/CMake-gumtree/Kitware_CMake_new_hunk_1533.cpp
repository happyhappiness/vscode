    {

      if (k != -1)

        errno = EINVAL;

      if (pathname)

        {

        free(pathname);

        }

      return -1;

    }



    /* write block to output file */

    if (write(fdout, buf,

        ((i > T_BLOCKSIZE) ? T_BLOCKSIZE : i)) == -1)

      {

      if (pathname)

        {

        free(pathname);

        }

      return -1;

      }

  }



  /* close output file */

  if (close(fdout) == -1)

    {

    if (pathname)

      {

      free(pathname);

      }

    return -1;

    }



#ifdef DEBUG

  printf("### done extracting %s\n", filename);

