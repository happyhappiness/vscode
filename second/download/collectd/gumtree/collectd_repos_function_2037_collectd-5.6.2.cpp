static int ctail_read(user_data_t *ud) {
  int status;

  status = tail_match_read((cu_tail_match_t *)ud->data);
  if (status != 0) {
    ERROR("tail plugin: tail_match_read failed.");
    return (-1);
  }

  return (0);
}