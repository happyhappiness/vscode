(fgets(buf, sizeof(buf), statfile_fp)) {
    if (strncmp(buf, "cpu", 3))
      break;
    num++;
  }