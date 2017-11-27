static jobject ctoj_data_set(JNIEnv *jvm_env, const data_set_t *ds) /* {{{ */
{
  jclass c_dataset;
  jmethodID m_constructor;
  jmethodID m_add;
  jobject o_type;
  jobject o_dataset;

  /* Look up the org/collectd/api/DataSet class */
  c_dataset = (*jvm_env)->FindClass(jvm_env, "org/collectd/api/DataSet");
  if (c_dataset == NULL) {
    ERROR("java plugin: ctoj_data_set: Looking up the "
          "org/collectd/api/DataSet class failed.");
    return (NULL);
  }

  /* Search for the `DataSet (String type)' constructor. */
  m_constructor = (*jvm_env)->GetMethodID(jvm_env, c_dataset, "<init>",
                                          "(Ljava/lang/String;)V");
  if (m_constructor == NULL) {
    ERROR("java plugin: ctoj_data_set: Looking up the "
          "`DataSet (String)' constructor failed.");
    return (NULL);
  }

  /* Search for the `void addDataSource (DataSource)' method. */
  m_add = (*jvm_env)->GetMethodID(jvm_env, c_dataset, "addDataSource",
                                  "(Lorg/collectd/api/DataSource;)V");
  if (m_add == NULL) {
    ERROR("java plugin: ctoj_data_set: Looking up the "
          "`addDataSource (DataSource)' method failed.");
    return (NULL);
  }

  o_type = (*jvm_env)->NewStringUTF(jvm_env, ds->type);
  if (o_type == NULL) {
    ERROR("java plugin: ctoj_data_set: Creating a String object failed.");
    return (NULL);
  }

  o_dataset = (*jvm_env)->NewObject(jvm_env, c_dataset, m_constructor, o_type);
  if (o_dataset == NULL) {
    ERROR("java plugin: ctoj_data_set: Creating a DataSet object failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_type);
    return (NULL);
  }

  /* Decrease reference counter on the java.lang.String object. */
  (*jvm_env)->DeleteLocalRef(jvm_env, o_type);

  for (size_t i = 0; i < ds->ds_num; i++) {
    jobject o_datasource;

    o_datasource = ctoj_data_source(jvm_env, ds->ds + i);
    if (o_datasource == NULL) {
      ERROR("java plugin: ctoj_data_set: ctoj_data_source (%s.%s) failed",
            ds->type, ds->ds[i].name);
      (*jvm_env)->DeleteLocalRef(jvm_env, o_dataset);
      return (NULL);
    }

    (*jvm_env)->CallVoidMethod(jvm_env, o_dataset, m_add, o_datasource);

    (*jvm_env)->DeleteLocalRef(jvm_env, o_datasource);
  } /* for (i = 0; i < ds->ds_num; i++) */

  return (o_dataset);
}