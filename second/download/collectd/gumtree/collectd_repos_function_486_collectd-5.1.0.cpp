static jobject ctoj_data_source (JNIEnv *jvm_env, /* {{{ */
    const data_source_t *dsrc)
{
  jclass c_datasource;
  jmethodID m_datasource_constructor;
  jobject o_datasource;
  int status;

  /* Look up the DataSource class */
  c_datasource = (*jvm_env)->FindClass (jvm_env,
      "org/collectd/api/DataSource");
  if (c_datasource == NULL)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "FindClass (org/collectd/api/DataSource) failed.");
    return (NULL);
  }

  /* Lookup the `ValueList ()' constructor. */
  m_datasource_constructor = (*jvm_env)->GetMethodID (jvm_env, c_datasource,
      "<init>", "()V");
  if (m_datasource_constructor == NULL)
  {
    ERROR ("java plugin: ctoj_data_source: Cannot find the "
        "`DataSource ()' constructor.");
    return (NULL);
  }

  /* Create a new instance. */
  o_datasource = (*jvm_env)->NewObject (jvm_env, c_datasource,
      m_datasource_constructor);
  if (o_datasource == NULL)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "Creating a new DataSource instance failed.");
    return (NULL);
  }

  /* Set name via `void setName (String name)' */
  status = ctoj_string (jvm_env, dsrc->name,
      c_datasource, o_datasource, "setName");
  if (status != 0)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "ctoj_string (setName) failed.");
    (*jvm_env)->DeleteLocalRef (jvm_env, o_datasource);
    return (NULL);
  }

  /* Set type via `void setType (int type)' */
  status = ctoj_int (jvm_env, dsrc->type,
      c_datasource, o_datasource, "setType");
  if (status != 0)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "ctoj_int (setType) failed.");
    (*jvm_env)->DeleteLocalRef (jvm_env, o_datasource);
    return (NULL);
  }

  /* Set min via `void setMin (double min)' */
  status = ctoj_double (jvm_env, dsrc->min,
      c_datasource, o_datasource, "setMin");
  if (status != 0)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "ctoj_double (setMin) failed.");
    (*jvm_env)->DeleteLocalRef (jvm_env, o_datasource);
    return (NULL);
  }

  /* Set max via `void setMax (double max)' */
  status = ctoj_double (jvm_env, dsrc->max,
      c_datasource, o_datasource, "setMax");
  if (status != 0)
  {
    ERROR ("java plugin: ctoj_data_source: "
        "ctoj_double (setMax) failed.");
    (*jvm_env)->DeleteLocalRef (jvm_env, o_datasource);
    return (NULL);
  }

  return (o_datasource);
}