static void destroy_callback(callback_func_t *cf) /* {{{ */
{
  if (cf == NULL)
    return;

  if ((cf->cf_udata.data != NULL) && (cf->cf_udata.free_func != NULL)) {
    cf->cf_udata.free_func(cf->cf_udata.data);
    cf->cf_udata.data = NULL;
    cf->cf_udata.free_func = NULL;
  }
  sfree(cf);
}