{
    errno = 0;
    if (fgets(buf, bufSize, file) == 0) {
      if (ferror(file) && (errno == EINTR)) {
        clearerr(file);
      }
      continue;
    }
    char* pBuf = buf;
    while (*pBuf) {
      if (*pBuf == '\n')
        *pBuf = '\0';
      pBuf += 1;
    }
    lines.push_back(buf);
    ++nRead;
  }