      | 0) == -1)
    {
    fprintf(stderr, "tar_open(): %s\n", strerror(errno));
    return false;
    }

  std::vector<cmStdString>::const_iterator it;
