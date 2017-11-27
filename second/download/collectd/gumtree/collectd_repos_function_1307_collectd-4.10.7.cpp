static void o_report_error (const char *where, /* {{{ */
    const char *what, OCIError *eh)
{
  char buffer[2048];
  sb4 error_code;
  int status;
  unsigned int record_number;

  /* An operation may cause / return multiple errors. Loop until we have
   * handled all errors available (with a fail-save limit of 16). */
  for (record_number = 1; record_number <= 16; record_number++)
  {
    memset (buffer, 0, sizeof (buffer));
    error_code = -1;

    status = OCIErrorGet (eh, (ub4) record_number,
        /* sqlstate = */ NULL,
        &error_code,
        (text *) &buffer[0],
        (ub4) sizeof (buffer),
        OCI_HTYPE_ERROR);
    buffer[sizeof (buffer) - 1] = 0;

    if (status == OCI_NO_DATA)
      return;

    if (status == OCI_SUCCESS)
    {
      size_t buffer_length;

      buffer_length = strlen (buffer);
      while ((buffer_length > 0) && (buffer[buffer_length - 1] < 32))
      {
        buffer_length--;
        buffer[buffer_length] = 0;
      }

      ERROR ("oracle plugin: %s: %s failed: %s", where, what, buffer);
    }
    else
    {
      ERROR ("oracle plugin: %s: %s failed. Additionally, OCIErrorGet failed with status %i.",
          where, what, status);
      return;
    }
  }
}