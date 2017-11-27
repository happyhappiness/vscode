static jobject ctoj_oconfig_value (JNIEnv *jvm_env, /* {{{ */
    oconfig_value_t ocvalue)
{
  jclass c_ocvalue;
  jmethodID m_ocvalue_constructor;
  jobject o_argument;
  jobject o_ocvalue;

  m_ocvalue_constructor = NULL;
  o_argument = NULL;

  c_ocvalue = (*jvm_env)->FindClass (jvm_env,
      "org/collectd/api/OConfigValue");
  if (c_ocvalue == NULL)
  {
    ERROR ("java plugin: ctoj_oconfig_value: "
        "FindClass (org/collectd/api/OConfigValue) failed.");
    return (NULL);
  }

  if (ocvalue.type == OCONFIG_TYPE_BOOLEAN)
  {
    jboolean tmp_boolean;

    tmp_boolean = (ocvalue.value.boolean == 0) ? JNI_FALSE : JNI_TRUE;

    m_ocvalue_constructor = (*jvm_env)->GetMethodID (jvm_env, c_ocvalue,
        "<init>", "(Z)V");
    if (m_ocvalue_constructor == NULL)
    {
      ERROR ("java plugin: ctoj_oconfig_value: Cannot find the "
          "`OConfigValue (boolean)' constructor.");
      return (NULL);
    }

    return ((*jvm_env)->NewObject (jvm_env,
          c_ocvalue, m_ocvalue_constructor, tmp_boolean));
  } /* if (ocvalue.type == OCONFIG_TYPE_BOOLEAN) */
  else if (ocvalue.type == OCONFIG_TYPE_STRING)
  {
    m_ocvalue_constructor = (*jvm_env)->GetMethodID (jvm_env, c_ocvalue,
        "<init>", "(Ljava/lang/String;)V");
    if (m_ocvalue_constructor == NULL)
    {
      ERROR ("java plugin: ctoj_oconfig_value: Cannot find the "
          "`OConfigValue (String)' constructor.");
      return (NULL);
    }

    o_argument = (*jvm_env)->NewStringUTF (jvm_env, ocvalue.value.string);
    if (o_argument == NULL)
    {
      ERROR ("java plugin: ctoj_oconfig_value: "
          "Creating a String object failed.");
      return (NULL);
    }
  }
  else if (ocvalue.type == OCONFIG_TYPE_NUMBER)
  {
    m_ocvalue_constructor = (*jvm_env)->GetMethodID (jvm_env, c_ocvalue,
        "<init>", "(Ljava/lang/Number;)V");
    if (m_ocvalue_constructor == NULL)
    {
      ERROR ("java plugin: ctoj_oconfig_value: Cannot find the "
          "`OConfigValue (Number)' constructor.");
      return (NULL);
    }

    o_argument = ctoj_jdouble_to_number (jvm_env,
        (jdouble) ocvalue.value.number);
    if (o_argument == NULL)
    {
      ERROR ("java plugin: ctoj_oconfig_value: "
          "Creating a Number object failed.");
      return (NULL);
    }
  }
  else
  {
    return (NULL);
  }

  assert (m_ocvalue_constructor != NULL);
  assert (o_argument != NULL);

  o_ocvalue = (*jvm_env)->NewObject (jvm_env,
      c_ocvalue, m_ocvalue_constructor, o_argument);
  if (o_ocvalue == NULL)
  {
    ERROR ("java plugin: ctoj_oconfig_value: "
        "Creating an OConfigValue object failed.");
    (*jvm_env)->DeleteLocalRef (jvm_env, o_argument);
    return (NULL);
  }

  (*jvm_env)->DeleteLocalRef (jvm_env, o_argument);
  return (o_ocvalue);
}