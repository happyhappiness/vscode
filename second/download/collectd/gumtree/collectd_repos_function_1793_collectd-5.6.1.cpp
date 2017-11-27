static void o_report_error (const char *where, /* {{{ */
    const char *db_name, const char *query_name,
    const char *what, OCIError *eh)
{
  char buffer[2048];
  sb4 error_code;
  int status;

  if (db_name == NULL)
    db_name = "(none)";
  if (query_name == NULL)
    query_name = "(none)";

  /* An operation may cause / return multiple errors. Loop until we have
   * handled all errors available (with a fail-save limit of 16). */
  for (unsigned int record_number = 1; record_number <= 16; record_number++)
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

      ERROR ("oracle plugin: %s (db = %s, query = %s): %s failed: %s",
          where, db_name, query_name, what, buffer);
    }
    else
    {
      ERROR ("oracle plugin: %s (db = %s, query = %s): %s failed. "
          "Additionally, OCIErrorGet failed with status %i.",
          where, db_name, query_name, what, status);
      return;
    }
  }
}