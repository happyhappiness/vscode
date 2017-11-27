static jobject ctoj_oconfig_item(JNIEnv *jvm_env, /* {{{ */
                                 const oconfig_item_t *ci) {
  jclass c_ocitem;
  jmethodID m_ocitem_constructor;
  jmethodID m_addvalue;
  jmethodID m_addchild;
  jobject o_key;
  jobject o_ocitem;

  c_ocitem = (*jvm_env)->FindClass(jvm_env, "org/collectd/api/OConfigItem");
  if (c_ocitem == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: "
          "FindClass (org/collectd/api/OConfigItem) failed.");
    return NULL;
  }

  /* Get the required methods: m_ocitem_constructor, m_addvalue, and m_addchild
   * {{{ */
  m_ocitem_constructor = (*jvm_env)->GetMethodID(jvm_env, c_ocitem, "<init>",
                                                 "(Ljava/lang/String;)V");
  if (m_ocitem_constructor == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: Cannot find the "
          "`OConfigItem (String)' constructor.");
    return NULL;
  }

  m_addvalue = (*jvm_env)->GetMethodID(jvm_env, c_ocitem, "addValue",
                                       "(Lorg/collectd/api/OConfigValue;)V");
  if (m_addvalue == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: Cannot find the "
          "`addValue (OConfigValue)' method.");
    return NULL;
  }

  m_addchild = (*jvm_env)->GetMethodID(jvm_env, c_ocitem, "addChild",
                                       "(Lorg/collectd/api/OConfigItem;)V");
  if (m_addchild == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: Cannot find the "
          "`addChild (OConfigItem)' method.");
    return NULL;
  }
  /* }}} */

  /* Create a String object with the key.
   * Needed for calling the constructor. */
  o_key = (*jvm_env)->NewStringUTF(jvm_env, ci->key);
  if (o_key == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: "
          "Creating String object failed.");
    return NULL;
  }

  /* Create an OConfigItem object */
  o_ocitem =
      (*jvm_env)->NewObject(jvm_env, c_ocitem, m_ocitem_constructor, o_key);
  if (o_ocitem == NULL) {
    ERROR("java plugin: ctoj_oconfig_item: "
          "Creating an OConfigItem object failed.");
    (*jvm_env)->DeleteLocalRef(jvm_env, o_key);
    return NULL;
  }

  /* We don't need the String object any longer.. */
  (*jvm_env)->DeleteLocalRef(jvm_env, o_key);

  /* Call OConfigItem.addValue for each value */
  for (int i = 0; i < ci->values_num; i++) /* {{{ */
  {
    jobject o_value;

    o_value = ctoj_oconfig_value(jvm_env, ci->values[i]);
    if (o_value == NULL) {
      ERROR("java plugin: ctoj_oconfig_item: "
            "Creating an OConfigValue object failed.");
      (*jvm_env)->DeleteLocalRef(jvm_env, o_ocitem);
      return NULL;
    }

    (*jvm_env)->CallVoidMethod(jvm_env, o_ocitem, m_addvalue, o_value);
    (*jvm_env)->DeleteLocalRef(jvm_env, o_value);
  } /* }}} for (i = 0; i < ci->values_num; i++) */

  /* Call OConfigItem.addChild for each child */
  for (int i = 0; i < ci->children_num; i++) /* {{{ */
  {
    jobject o_child;

    o_child = ctoj_oconfig_item(jvm_env, ci->children + i);
    if (o_child == NULL) {
      ERROR("java plugin: ctoj_oconfig_item: "
            "Creating an OConfigItem object failed.");
      (*jvm_env)->DeleteLocalRef(jvm_env, o_ocitem);
      return NULL;
    }

    (*jvm_env)->CallVoidMethod(jvm_env, o_ocitem, m_addchild, o_child);
    (*jvm_env)->DeleteLocalRef(jvm_env, o_child);
  } /* }}} for (i = 0; i < ci->children_num; i++) */

  return o_ocitem;
}