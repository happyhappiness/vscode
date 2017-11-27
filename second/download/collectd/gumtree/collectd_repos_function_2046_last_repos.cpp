static int o_shutdown(void) /* {{{ */
{
  size_t i;

  for (i = 0; i < databases_num; i++)
    if (databases[i]->oci_service_context != NULL) {
      OCIHandleFree(databases[i]->oci_service_context, OCI_HTYPE_SVCCTX);
      databases[i]->oci_service_context = NULL;
    }

  for (i = 0; i < queries_num; i++) {
    OCIStmt *oci_statement;

    oci_statement = udb_query_get_user_data(queries[i]);
    if (oci_statement != NULL) {
      OCIHandleFree(oci_statement, OCI_HTYPE_STMT);
      udb_query_set_user_data(queries[i], NULL);
    }
  }

  OCIHandleFree(oci_env, OCI_HTYPE_ENV);
  oci_env = NULL;

  udb_query_free(queries, queries_num);
  queries = NULL;
  queries_num = 0;

  return 0;
}