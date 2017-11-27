static int o_read_database (o_database_t *db) /* {{{ */
{
  size_t i;
  int status;

  if (db->oci_service_context == NULL)
  {
    status = OCILogon (oci_env, oci_error,
        &db->oci_service_context,
        (OraText *) db->username, (ub4) strlen (db->username),
        (OraText *) db->password, (ub4) strlen (db->password),
        (OraText *) db->connect_id, (ub4) strlen (db->connect_id));
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database", "OCILogon", oci_error);
      DEBUG ("oracle plugin: OCILogon (%s): db->oci_service_context = %p;",
          db->connect_id, db->oci_service_context);
      db->oci_service_context = NULL;
      return (-1);
    }
    assert (db->oci_service_context != NULL);
  }

  DEBUG ("oracle plugin: o_read_database: db->connect_id = %s; db->oci_service_context = %p;",
      db->connect_id, db->oci_service_context);

  for (i = 0; i < db->queries_num; i++)
    o_read_database_query (db, db->queries[i]);

  return (0);
}