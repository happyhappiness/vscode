static int jtoc_values_array(JNIEnv *jvm_env, /* {{{ */
                             const data_set_t *ds, value_list_t *vl,
                             jclass class_ptr, jobject object_ptr) {
  jmethodID m_getvalues;
  jmethodID m_toarray;
  jobject o_list;
  jobjectArray o_number_array;

  value_t *values;
  int values_num;

  values_num = ds->ds_num;

  values = NULL;
  o_number_array = NULL;
  o_list = NULL;

#define BAIL_OUT(status)                                                       \
  free(values);                                                                \
  if (o_number_array != NULL)                                                  \
    (*jvm_env)->DeleteLocalRef(jvm_env, o_number_array);                       \
  if (o_list != NULL)                                                          \
    (*jvm_env)->DeleteLocalRef(jvm_env, o_list);                               \
  return (status);

  /* Call: List<Number> ValueList.getValues () */
  m_getvalues = (*jvm_env)->GetMethodID(jvm_env, class_ptr, "getValues",
                                        "()Ljava/util/List;");
  if (m_getvalues == NULL) {
    ERROR("java plugin: jtoc_values_array: "
          "Cannot find method `List getValues ()'.");
    BAIL_OUT(-1);
  }

  o_list = (*jvm_env)->CallObjectMethod(jvm_env, object_ptr, m_getvalues);
  if (o_list == NULL) {
    ERROR("java plugin: jtoc_values_array: "
          "CallObjectMethod (getValues) failed.");
    BAIL_OUT(-1);
  }

  /* Call: Number[] List.toArray () */
  m_toarray = (*jvm_env)->GetMethodID(
      jvm_env, (*jvm_env)->GetObjectClass(jvm_env, o_list), "toArray",
      "()[Ljava/lang/Object;");
  if (m_toarray == NULL) {
    ERROR("java plugin: jtoc_values_array: "
          "Cannot find method `Object[] toArray ()'.");
    BAIL_OUT(-1);
  }

  o_number_array = (*jvm_env)->CallObjectMethod(jvm_env, o_list, m_toarray);
  if (o_number_array == NULL) {
    ERROR("java plugin: jtoc_values_array: "
          "CallObjectMethod (toArray) failed.");
    BAIL_OUT(-1);
  }

  values = (value_t *)calloc(values_num, sizeof(value_t));
  if (values == NULL) {
    ERROR("java plugin: jtoc_values_array: calloc failed.");
    BAIL_OUT(-1);
  }

  for (int i = 0; i < values_num; i++) {
    jobject o_number;
    int status;

    o_number =
        (*jvm_env)->GetObjectArrayElement(jvm_env, o_number_array, (jsize)i);
    if (o_number == NULL) {
      ERROR("java plugin: jtoc_values_array: "
            "GetObjectArrayElement (%i) failed.",
            i);
      BAIL_OUT(-1);
    }

    status = jtoc_value(jvm_env, values + i, ds->ds[i].type, o_number);
    if (status != 0) {
      ERROR("java plugin: jtoc_values_array: "
            "jtoc_value (%i) failed.",
            i);
      BAIL_OUT(-1);
    }
  } /* for (i = 0; i < values_num; i++) */

  vl->values = values;
  vl->values_len = values_num;

#undef BAIL_OUT
  (*jvm_env)->DeleteLocalRef(jvm_env, o_number_array);
  (*jvm_env)->DeleteLocalRef(jvm_env, o_list);
  return (0);
}