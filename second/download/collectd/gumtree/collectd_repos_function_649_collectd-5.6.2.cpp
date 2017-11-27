static jint JNICALL cjni_api_register_match_target(JNIEnv *jvm_env, /* {{{ */
                                                   jobject this, jobject o_name,
                                                   jobject o_match, int type) {
  int status;
  const char *c_name;

  c_name = (*jvm_env)->GetStringUTFChars(jvm_env, o_name, 0);
  if (c_name == NULL) {
    ERROR("java plugin: cjni_api_register_match_target: "
          "GetStringUTFChars failed.");
    return (-1);
  }

  status = cjni_callback_register(jvm_env, o_name, o_match, type);
  if (status != 0) {
    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
    return (-1);
  }

  if (type == CB_TYPE_MATCH) {
    match_proc_t m_proc = {0};

    m_proc.create = cjni_match_target_create;
    m_proc.destroy = cjni_match_target_destroy;
    m_proc.match = (void *)cjni_match_target_invoke;

    status = fc_register_match(c_name, m_proc);
  } else if (type == CB_TYPE_TARGET) {
    target_proc_t t_proc = {0};

    t_proc.create = cjni_match_target_create;
    t_proc.destroy = cjni_match_target_destroy;
    t_proc.invoke = cjni_match_target_invoke;

    status = fc_register_target(c_name, t_proc);
  } else {
    ERROR("java plugin: cjni_api_register_match_target: "
          "Don't know whether to create a match or a target.");
    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
    return (-1);
  }

  if (status != 0) {
    ERROR("java plugin: cjni_api_register_match_target: "
          "%s failed.",
          (type == CB_TYPE_MATCH) ? "fc_register_match" : "fc_register_target");
    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
    return (-1);
  }

  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);

  return (0);
}