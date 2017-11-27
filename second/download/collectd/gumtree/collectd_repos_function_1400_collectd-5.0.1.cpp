static void o_report_error (const char *where, /* {{{ */
    const char *what, OCIError *eh)
{
  char buffer[2048];
  sb4 error_code;
  int status;

  status = OCIErrorGet (eh, /* record number = */ 1,
      /* sqlstate = */ NULL,
      &error_code,
      (text *) &buffer[0],
      (ub4) sizeof (buffer),
      OCI_HTYPE_ERROR);
  buffer[sizeof (buffer) - 1] = 0;

  if (status == OCI_SUCCESS)
  {
    size_t buffer_length;

    buffer_length = strlen (buffer);
    while ((buffer_length > 0) && (buffer[buffer_length - 1] < 32))
    {
      buffer_length--;
      buffer[buffer_length] = 0;
    }

    ERROR ("oracle plugin: %s: %s failed: %s",
        where, what, buffer);
  }
  else
  {
    ERROR ("oracle plugin: %s: %s failed. Additionally, OCIErrorGet failed with status %i.",
        where, what, status);
  }
}