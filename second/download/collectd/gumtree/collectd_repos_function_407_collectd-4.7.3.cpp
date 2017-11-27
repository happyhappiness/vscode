static int cjni_init_native (JNIEnv *jvm_env) /* {{{ */
{
  jclass api_class_ptr;
  int status;

  api_class_ptr = (*jvm_env)->FindClass (jvm_env, "org/collectd/api/Collectd");
  if (api_class_ptr == NULL)
  {
    ERROR ("cjni_init_native: Cannot find API class `org/collectd/api/Collectd'.");
    return (-1);
  }

  status = (*jvm_env)->RegisterNatives (jvm_env, api_class_ptr,
      jni_api_functions, (jint) jni_api_functions_num);
  if (status != 0)
  {
    ERROR ("cjni_init_native: RegisterNatives failed with status %i.", status);
    return (-1);
  }

  return (0);
}