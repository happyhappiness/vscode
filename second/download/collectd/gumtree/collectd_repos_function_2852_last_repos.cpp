static void destroy_callback(callback_func_t *cf) /* {{{ */
{
  if (cf == NULL)
    return;
  free_userdata(&cf->cf_udata);
  sfree(cf);
}