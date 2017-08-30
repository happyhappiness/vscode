        "tar_append_tree(\"%s\", \"%s\"): %s\n", buf,

        pathname, strerror(errno));

      tar_close(t);

      return -1;

      }

    }



  if (tar_append_eof(t) != 0)

    {

    fprintf(stderr, "tar_append_eof(): %s\n", strerror(errno));

    tar_close(t);

    return -1;

    }



  if (tar_close(t) != 0)

    {

    fprintf(stderr, "tar_close(): %s\n", strerror(errno));

    return -1;

    }

  std::cout << "CreateTar: " << outFileName << std::endl;

  return false;

}
