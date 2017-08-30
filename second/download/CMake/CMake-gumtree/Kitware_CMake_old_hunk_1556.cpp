      | 0) == -1)
    {
    fprintf(stderr, "tar_open(): %s\n", strerror(errno));
    return -1;
    }

  std::vector<cmStdString>::const_iterator it;
