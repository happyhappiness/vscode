static int o_read_database (o_database_t *db) /* {{{ */
{
  size_t i;
  int status;

  if (db->oci_service_context != NULL)
  {
    OCIServer *server_handle;
    ub4 connection_status;

    server_handle = NULL;
    status = OCIAttrGet ((void *) db->oci_service_context, OCI_HTYPE_SVCCTX, 
        (void *) &server_handle, /* size pointer = */ NULL,
        OCI_ATTR_SERVER, oci_error);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database", db->name, NULL, "OCIAttrGet",
          oci_error);
      return (-1);
    }

    if (server_handle == NULL)
    {
      connection_status = OCI_SERVER_NOT_CONNECTED;
    }
    else /* if (server_handle != NULL) */
    {
      connection_status = 0;
      status = OCIAttrGet ((void *) server_handle, OCI_HTYPE_SERVER,
          (void *) &connection_status, /* size pointer = */ NULL,
          OCI_ATTR_SERVER_STATUS, oci_error);
      if (status != OCI_SUCCESS)
      {
        o_report_error ("o_read_database", db->name, NULL, "OCIAttrGet",
            oci_error);
        return (-1);
      }
    }

    if (connection_status != OCI_SERVER_NORMAL)
    {
      INFO ("oracle plugin: Connection to %s lost. Trying to reconnect.",
          db->name);
      OCIHandleFree (db->oci_service_context, OCI_HTYPE_SVCCTX);
      db->oci_service_context = NULL;
    }
  } /* if (db->oci_service_context != NULL) */

  if (db->oci_service_context == NULL)
  {
    status = OCILogon (oci_env, oci_error,
        &db->oci_service_context,
        (OraText *) db->username, (ub4) strlen (db->username),
        (OraText *) db->password, (ub4) strlen (db->password),
        (OraText *) db->connect_id, (ub4) strlen (db->connect_id));
    if ((status != OCI_SUCCESS) && (status != OCI_SUCCESS_WITH_INFO))
    {
      char errfunc[256];

      ssnprintf (errfunc, sizeof (errfunc), "OCILogon(\"%s\")", db->connect_id);

      o_report_error ("o_read_database", db->name, NULL, errfunc, oci_error);
      DEBUG ("oracle plugin: OCILogon (%s): db->oci_service_context = %p;",
          db->connect_id, db->oci_service_context);
      db->oci_service_context = NULL;
      return (-1);
    }
    else if (status == OCI_SUCCESS_WITH_INFO)
    {
      /* TODO: Print NOTIFY message. */
    }
    assert (db->oci_service_context != NULL);
  }

  DEBUG ("oracle plugin: o_read_database: db->connect_id = %s; db->oci_service_context = %p;",
      db->connect_id, db->oci_service_context);

  for (i = 0; i < db->queries_num; i++)
    o_read_database_query (db, db->queries[i], db->q_prep_areas[i]);

  return (0);
}