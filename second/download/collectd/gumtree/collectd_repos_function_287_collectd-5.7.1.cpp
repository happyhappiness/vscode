static void varnish_config_free(void *ptr) /* {{{ */
{
  user_config_t *conf = ptr;

  if (conf == NULL)
    return;

  sfree(conf->instance);
  sfree(conf);
}