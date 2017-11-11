static void krb5_end(void *app_data)
{
    OM_uint32 min;
    gss_ctx_id_t *context = app_data;
    if(*context != GSS_C_NO_CONTEXT) {
#ifdef DEBUGBUILD
      OM_uint32 maj =
#endif
      gss_delete_sec_context(&min, context, GSS_C_NO_BUFFER);
      DEBUGASSERT(maj == GSS_S_COMPLETE);
    }
}