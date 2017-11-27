static int multimeter_read_value(double *value) {
  int retry = 3; /* sometimes we receive garbadge */

  do {
    struct timeval time_end;

    tcflush(fd, TCIFLUSH);

    if (gettimeofday(&time_end, NULL) < 0) {
      char errbuf[1024];
      ERROR("multimeter plugin: gettimeofday failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (-1);
    }
    time_end.tv_sec++;

    while (1) {
      char buf[LINE_LENGTH];
      char *range;
      int status;
      fd_set rfds;
      struct timeval timeout;
      struct timeval time_now;

      status = swrite(fd, "D", 1);
      if (status < 0) {
        ERROR("multimeter plugin: swrite failed.");
        return (-1);
      }

      FD_ZERO(&rfds);
      FD_SET(fd, &rfds);

      if (gettimeofday(&time_now, NULL) < 0) {
        char errbuf[1024];
        ERROR("multimeter plugin: "
              "gettimeofday failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
        return (-1);
      }
      if (timeval_cmp(time_end, time_now, &timeout) < 0)
        break;

      status = select(fd + 1, &rfds, NULL, NULL, &timeout);

      if (status > 0) /* usually we succeed */
      {
        status = read(fd, buf, LINE_LENGTH);

        if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
          continue;

        /* Format: "DC 00.000mV  \r" */
        if (status > 0 && status == LINE_LENGTH) {
          *value = strtod(buf + 2, &range);

          if (range > (buf + 6)) {
            range = buf + 9;

            switch (*range) {
            case 'p':
              *value *= 1.0E-12;
              break;
            case 'n':
              *value *= 1.0E-9;
              break;
            case 'u':
              *value *= 1.0E-6;
              break;
            case 'm':
              *value *= 1.0E-3;
              break;
            case 'k':
              *value *= 1.0E3;
              break;
            case 'M':
              *value *= 1.0E6;
              break;
            case 'G':
              *value *= 1.0E9;
              break;
            }
          } else
            return (-1); /* Overflow */

          return (0); /* value received */
        } else
          break;
      } else if (!status) /* Timeout */
      {
        break;
      } else if ((status == -1) && ((errno == EAGAIN) || (errno == EINTR))) {
        continue;
      } else /* status == -1 */
      {
        char errbuf[1024];
        ERROR("multimeter plugin: "
              "select failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
        break;
      }
    }
  } while (--retry);

  return (-2); /* no value received */
}