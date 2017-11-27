int tail_match_read(cu_tail_match_t *obj) {
  char buffer[4096];
  int status;

  status = cu_tail_read(obj->tail, buffer, sizeof(buffer), tail_callback,
                        (void *)obj);
  if (status != 0) {
    ERROR("tail_match: cu_tail_read failed.");
    return (status);
  }

  for (size_t i = 0; i < obj->matches_num; i++) {
    cu_tail_match_match_t *lt_match = obj->matches + i;

    if (lt_match->submit == NULL)
      continue;

    (*lt_match->submit)(lt_match->match, lt_match->user_data);
  }

  return (0);
}