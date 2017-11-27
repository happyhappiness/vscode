static int ctoj_value_list_add_data_set(JNIEnv *jvm_env, /* {{{ */
                                        jclass c_valuelist, jobject o_valuelist,
                                        const data_set_t *ds) {
  jmethodID m_setdataset;
  jobject o_dataset;

  /* Look for the `void setDataSource (List<DataSource> ds)' method. */
  m_setdataset = (*jvm_env)->GetMethodID(jvm_env, c_valuelist, "setDataSet",
                                         "(Lorg/collectd/api/DataSet;)V");
  if (m_setdataset == NULL) {
    ERROR("java plugin: ctoj_value_list_add_data_set: "
          "Cannot find the `void setDataSet (DataSet)' method.");
    return (-1);
  }

  /* Create a DataSet object. */
  o_dataset = ctoj_data_set(jvm_env, ds);
  if (o_dataset == NULL) {
    ERROR("java plugin: ctoj_value_list_add_data_set: "
          "ctoj_data_set (%s) failed.",
          ds->type);
    return (-1);
  }

  /* Actually call the method. */
  (*jvm_env)->CallVoidMethod(jvm_env, o_valuelist, m_setdataset, o_dataset);

  /* Decrease reference counter on the List<DataSource> object. */
  (*jvm_env)->DeleteLocalRef(jvm_env, o_dataset);

  return (0);
}