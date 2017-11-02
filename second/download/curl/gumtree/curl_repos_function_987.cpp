static int
krb5_init(void *app_data)
{
  gss_ctx_id_t *context = app_data;
  /* Make sure our context is initialized for krb5_end. */
  *context = GSS_C_NO_CONTEXT;
  return 0;
}