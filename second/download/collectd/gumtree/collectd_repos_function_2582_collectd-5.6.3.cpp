static int create_register_callback(llist_t **list, /* {{{ */
                                    const char *name, void *callback,
                                    user_data_t const *ud) {
  callback_func_t *cf;

  cf = calloc(1, sizeof(*cf));
  if (cf == NULL) {
    ERROR("plugin: create_register_callback: calloc failed.");
    return (-1);
  }

  cf->cf_callback = callback;
  if (ud == NULL) {
    cf->cf_udata.data = NULL;
    cf->cf_udata.free_func = NULL;
  } else {
    cf->cf_udata = *ud;
  }

  cf->cf_ctx = plugin_get_ctx();

  return (register_callback(list, name, cf));
}