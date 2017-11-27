static jstring ctoj_output_string (JNIEnv *jvm_env, /* {{{ */
    const char *string)
{
  jstring o_string;

  /* Create a java.lang.String */
  o_string = (*jvm_env)->NewStringUTF (jvm_env,
      (string != NULL) ? string : "");
  if (o_string == NULL)
  {
    ERROR ("java plugin: ctoj_output_string: NewStringUTF failed.");
    return NULL;
  }

  return (o_string);
}