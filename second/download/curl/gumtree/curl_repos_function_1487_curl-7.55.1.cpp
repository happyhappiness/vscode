static size_t tftp_option_add(tftp_state_data_t *state, size_t csize,
                              char *buf, const char *option)
{
  if(( strlen(option) + csize + 1) > (size_t)state->blksize)
    return 0;
  strcpy(buf, option);
  return strlen(option) + 1;
}