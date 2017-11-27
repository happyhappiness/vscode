static int o_read_database_query (o_database_t *db, /* {{{ */
    udb_query_t *q)
{
  char **column_names;
  char **column_values;
  size_t column_num;

  OCIStmt *oci_statement;

  /* List of `OCIDefine' pointers. These defines map columns to the buffer
   * space declared above. */
  OCIDefine **oci_defines;

  int status;
  size_t i;

  oci_statement = udb_query_get_user_data (q);

  /* Prepare the statement */
  if (oci_statement == NULL) /* {{{ */
  {
    const char *statement;

    statement = udb_query_get_statement (q);
    assert (statement != NULL);

    status = OCIHandleAlloc (oci_env, (void *) &oci_statement,
        OCI_HTYPE_STMT, /* user_data_size = */ 0, /* user_data = */ NULL);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database_query", "OCIHandleAlloc", oci_error);
      oci_statement = NULL;
      return (-1);
    }

    status = OCIStmtPrepare (oci_statement, oci_error,
        (text *) statement, (ub4) strlen (statement),
        /* language = */ OCI_NTV_SYNTAX,
        /* mode     = */ OCI_DEFAULT);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database_query", "OCIStmtPrepare", oci_error);
      OCIHandleFree (oci_statement, OCI_HTYPE_STMT);
      oci_statement = NULL;
      return (-1);
    }
    udb_query_set_user_data (q, oci_statement);

    DEBUG ("oracle plugin: o_read_database_query (%s, %s): "
        "Successfully allocated statement handle.",
        db->name, udb_query_get_name (q));
  } /* }}} */

  assert (oci_statement != NULL);

  /* Execute the statement */
  status = OCIStmtExecute (db->oci_service_context, /* {{{ */
      oci_statement,
      oci_error,
      /* iters = */ 0,
      /* rowoff = */ 0,
      /* snap_in = */ NULL, /* snap_out = */ NULL,
      /* mode = */ OCI_DEFAULT);
  if (status != OCI_SUCCESS)
  {
    DEBUG ("oracle plugin: o_read_database_query: status = %i (%#x)", status, status);
    o_report_error ("o_read_database_query", "OCIStmtExecute", oci_error);
    ERROR ("oracle plugin: o_read_database_query: "
        "Failing statement was: %s", udb_query_get_statement (q));
    return (-1);
  } /* }}} */

  /* Acquire the number of columns returned. */
  do /* {{{ */
  {
    ub4 param_counter = 0;
    status = OCIAttrGet (oci_statement, OCI_HTYPE_STMT, /* {{{ */
        &param_counter, /* size pointer = */ NULL, 
        OCI_ATTR_PARAM_COUNT, oci_error);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database_query", "OCIAttrGet", oci_error);
      return (-1);
    } /* }}} */

    column_num = (size_t) param_counter;
  } while (0); /* }}} */

  /* Allocate the following buffers:
   * 
   *  +---------------+-----------------------------------+
   *  ! Name          ! Size                              !
   *  +---------------+-----------------------------------+
   *  ! column_names  ! column_num x DATA_MAX_NAME_LEN    !
   *  ! column_values ! column_num x DATA_MAX_NAME_LEN    !
   *  ! oci_defines   ! column_num x sizeof (OCIDefine *) !
   *  +---------------+-----------------------------------+
   *
   * {{{ */
#define NUMBER_BUFFER_SIZE 64

#define FREE_ALL \
  if (column_names != NULL) { \
    sfree (column_names[0]); \
    sfree (column_names); \
  } \
  if (column_values != NULL) { \
    sfree (column_values[0]); \
    sfree (column_values); \
  } \
  sfree (oci_defines)

#define ALLOC_OR_FAIL(ptr, ptr_size) \
  do { \
    size_t alloc_size = (size_t) ((ptr_size)); \
    (ptr) = malloc (alloc_size); \
    if ((ptr) == NULL) { \
      FREE_ALL; \
      ERROR ("oracle plugin: o_read_database_query: malloc failed."); \
      return (-1); \
    } \
    memset ((ptr), 0, alloc_size); \
  } while (0)

  /* Initialize everything to NULL so the above works. */
  column_names  = NULL;
  column_values = NULL;
  oci_defines   = NULL;

  ALLOC_OR_FAIL (column_names, column_num * sizeof (char *));
  ALLOC_OR_FAIL (column_names[0], column_num * DATA_MAX_NAME_LEN
      * sizeof (char));
  for (i = 1; i < column_num; i++)
    column_names[i] = column_names[i - 1] + DATA_MAX_NAME_LEN;

  ALLOC_OR_FAIL (column_values, column_num * sizeof (char *));
  ALLOC_OR_FAIL (column_values[0], column_num * DATA_MAX_NAME_LEN
      * sizeof (char));
  for (i = 1; i < column_num; i++)
    column_values[i] = column_values[i - 1] + DATA_MAX_NAME_LEN;

  ALLOC_OR_FAIL (oci_defines, column_num * sizeof (OCIDefine *));
  /* }}} End of buffer allocations. */

  /* ``Define'' the returned data, i. e. bind the columns to the buffers
   * allocated above. */
  for (i = 0; i < column_num; i++) /* {{{ */
  {
    char *column_name;
    size_t column_name_length;
    OCIParam *oci_param;

    oci_param = NULL;

    status = OCIParamGet (oci_statement, OCI_HTYPE_STMT, oci_error,
        (void *) &oci_param, (ub4) (i + 1));
    if (status != OCI_SUCCESS)
    {
      /* This is probably alright */
      DEBUG ("oracle plugin: o_read_database_query: status = %#x (= %i);", status, status);
      o_report_error ("o_read_database_query", "OCIParamGet", oci_error);
      status = OCI_SUCCESS;
      break;
    }

    column_name = NULL;
    column_name_length = 0;
    status = OCIAttrGet (oci_param, OCI_DTYPE_PARAM,
        &column_name, &column_name_length, OCI_ATTR_NAME, oci_error);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database_query", "OCIAttrGet (OCI_ATTR_NAME)",
          oci_error);
      continue;
    }

    /* Copy the name to column_names. Warning: The ``string'' returned by OCI
     * may not be null terminated! */
    memset (column_names[i], 0, DATA_MAX_NAME_LEN);
    if (column_name_length >= DATA_MAX_NAME_LEN)
      column_name_length = DATA_MAX_NAME_LEN - 1;
    memcpy (column_names[i], column_name, column_name_length);
    column_names[i][column_name_length] = 0;

    DEBUG ("oracle plugin: o_read_database_query: column_names[%zu] = %s; "
        "column_name_length = %zu;",
        i, column_names[i], column_name_length);

    status = OCIDefineByPos (oci_statement,
        &oci_defines[i], oci_error, (ub4) (i + 1),
        column_values[i], DATA_MAX_NAME_LEN, SQLT_STR,
        NULL, NULL, NULL, OCI_DEFAULT);
    if (status != OCI_SUCCESS)
    {
      o_report_error ("o_read_database_query", "OCIDefineByPos", oci_error);
      continue;
    }
  } /* for (j = 1; j <= param_counter; j++) */
  /* }}} End of the ``define'' stuff. */

  status = udb_query_prepare_result (q, hostname_g, /* plugin = */ "oracle",
      db->name, column_names, column_num);
  if (status != 0)
  {
    ERROR ("oracle plugin: o_read_database_query (%s, %s): "
        "udb_query_prepare_result failed.",
        db->name, udb_query_get_name (q));
    FREE_ALL;
    return (-1);
  }

  /* Fetch and handle all the rows that matched the query. */
  while (42) /* {{{ */
  {
    status = OCIStmtFetch2 (oci_statement, oci_error,
        /* nrows = */ 1, /* orientation = */ OCI_FETCH_NEXT,
        /* fetch offset = */ 0, /* mode = */ OCI_DEFAULT);
    if (status == OCI_NO_DATA)
    {
      status = OCI_SUCCESS;
      break;
    }
    else if ((status != OCI_SUCCESS) && (status != OCI_SUCCESS_WITH_INFO))
    {
      o_report_error ("o_read_database_query", "OCIStmtFetch2", oci_error);
      break;
    }

    status = udb_query_handle_result (q, column_values);
    if (status != 0)
    {
      WARNING ("oracle plugin: o_read_database_query (%s, %s): "
          "udb_query_handle_result failed.",
          db->name, udb_query_get_name (q));
    }
  } /* }}} while (42) */

  /* DEBUG ("oracle plugin: o_read_database_query: This statement succeeded: %s", q->statement); */
  FREE_ALL;

  return (0);
#undef FREE_ALL
#undef ALLOC_OR_FAIL
}