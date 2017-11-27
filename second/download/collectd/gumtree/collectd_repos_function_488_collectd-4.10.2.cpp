static void cjni_log (int severity, const char *message, /* {{{ */
    user_data_t *ud)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_message;

  if (jvm == NULL)
    return;

  if ((ud == NULL) || (ud->data == NULL))
    return;

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return;

  cbi = (cjni_callback_info_t *) ud->data;

  o_message = (*jvm_env)->NewStringUTF (jvm_env, message);
  if (o_message == NULL)
    return;

  (*jvm_env)->CallVoidMethod (jvm_env,
      cbi->object, cbi->method, (jint) severity, o_message);

  (*jvm_env)->DeleteLocalRef (jvm_env, o_message);

  cjni_thread_detach ();
}