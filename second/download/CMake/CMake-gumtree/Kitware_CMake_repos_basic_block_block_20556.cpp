{
    *size = 0;
    err = uv_translate_sys_error(pRtlNtStatusToDosError(nt_status));
    goto error;
  }