static int o_init (void) /* {{{ */
{
  int status;

  if (oci_env != NULL)
    return (0);

  status = OCIEnvCreate (&oci_env,
      /* mode = */ OCI_THREADED,
      /* context        = */ NULL,
      /* malloc         = */ NULL,
      /* realloc        = */ NULL,
      /* free           = */ NULL,
      /* user_data_size = */ 0,
      /* user_data_ptr  = */ NULL);
  if (status != 0)
  {
    ERROR ("oracle plugin: OCIEnvCreate failed with status %i.", status);
    return (-1);
  }

  status = OCIHandleAlloc (oci_env, (void *) &oci_error, OCI_HTYPE_ERROR,
      /* user_data_size = */ 0, /* user_data = */ NULL);
  if (status != OCI_SUCCESS)
  {
    ERROR ("oracle plugin: OCIHandleAlloc (OCI_HTYPE_ERROR) failed "
        "with status %i.", status);
    return (-1);
  }

  return (0);
}