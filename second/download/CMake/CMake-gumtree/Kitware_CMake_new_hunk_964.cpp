      else

        ret = ARCHIVE_FATAL;

    }

    return (ret);

  }



  /* Note: The "warn" return is just to inform the options

   * supervisor that we didn't handle it.  It will generate

   * a suitable error if no one used this option. */

  return (ARCHIVE_WARN);

}



static int

