        "tar_append_tree(\"%s\", \"%s\"): %s\n", buf,

        pathname, strerror(errno));

      tar_close(t);

      return false;

      }

    }



  if (tar_append_eof(t) != 0)

    {

    fprintf(stderr, "tar_append_eof(): %s\n", strerror(errno));

    tar_close(t);

    return false;

    }



  if (tar_close(t) != 0)

    {

    fprintf(stderr, "tar_close(): %s\n", strerror(errno));

    return false;

    }

  return true;

}
