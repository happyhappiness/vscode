static int lcc_receive(lcc_connection_t *c, /* {{{ */
                       lcc_response_t *ret_res) {
  lcc_response_t res = {0};
  char *ptr;
  char buffer[4096];
  size_t i;

  /* Read the first line, containing the status and a message */
  ptr = fgets(buffer, sizeof(buffer), c->fh);
  if (ptr == NULL) {
    lcc_set_errno(c, errno);
    return (-1);
  }
  lcc_chomp(buffer);
  lcc_tracef("receive: <-- %s\n", buffer);

  /* Convert the leading status to an integer and make `ptr' to point to the
   * beginning of the message. */
  ptr = NULL;
  errno = 0;
  res.status = (int)strtol(buffer, &ptr, 0);
  if ((errno != 0) || (ptr == &buffer[0])) {
    lcc_set_errno(c, errno);
    return (-1);
  }

  /* Skip white spaces after the status number */
  while ((*ptr == ' ') || (*ptr == '\t'))
    ptr++;

  /* Now copy the message. */
  strncpy(res.message, ptr, sizeof(res.message));
  res.message[sizeof(res.message) - 1] = 0;

  /* Error or no lines follow: We're done. */
  if (res.status <= 0) {
    memcpy(ret_res, &res, sizeof(res));
    return (0);
  }

  /* Allocate space for the char-pointers */
  res.lines_num = (size_t)res.status;
  res.status = 0;
  res.lines = malloc(res.lines_num * sizeof(*res.lines));
  if (res.lines == NULL) {
    lcc_set_errno(c, ENOMEM);
    return (-1);
  }

  /* Now receive all the lines */
  for (i = 0; i < res.lines_num; i++) {
    ptr = fgets(buffer, sizeof(buffer), c->fh);
    if (ptr == NULL) {
      lcc_set_errno(c, errno);
      break;
    }
    lcc_chomp(buffer);
    lcc_tracef("receive: <-- %s\n", buffer);

    res.lines[i] = strdup(buffer);
    if (res.lines[i] == NULL) {
      lcc_set_errno(c, ENOMEM);
      break;
    }
  }

  /* Check if the for-loop exited with an error. */
  if (i < res.lines_num) {
    while (i > 0) {
      i--;
      free(res.lines[i]);
    }
    free(res.lines);
    return (-1);
  }

  memcpy(ret_res, &res, sizeof(res));
  return (0);
}