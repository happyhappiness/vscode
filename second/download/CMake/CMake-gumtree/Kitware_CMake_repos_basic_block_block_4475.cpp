{
#ifdef DEBUGBUILD
      OM_uint32 maj =
#endif
      gss_delete_sec_context(&min, context, GSS_C_NO_BUFFER);
      DEBUGASSERT(maj == GSS_S_COMPLETE);
    }