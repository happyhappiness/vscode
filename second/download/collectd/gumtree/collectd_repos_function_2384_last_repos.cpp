static int cj_cb_map_key(void *ctx, unsigned char const *in_name,
                         yajl_len_t in_name_len) {
  char name[in_name_len + 1];

  memmove(name, in_name, in_name_len);
  name[sizeof(name) - 1] = 0;

  if (cj_load_key(ctx, name) != 0)
    return CJ_CB_ABORT;

  return CJ_CB_CONTINUE;
}