static int cjni_match_target_create (const oconfig_item_t *ci, /* {{{ */
    void **user_data)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi_ret;
  cjni_callback_info_t *cbi_factory;
  const char *name;
  jobject o_ci;
  jobject o_tmp;
  int type;
  size_t i;

  cbi_ret = NULL;
  o_ci = NULL;
  jvm_env = NULL;

#define BAIL_OUT(status) \
  if (cbi_ret != NULL) { \
    free (cbi_ret->name); \
    if ((jvm_env != NULL) && (cbi_ret->object != NULL)) \
      (*jvm_env)->DeleteLocalRef (jvm_env, cbi_ret->object); \
  } \
  free (cbi_ret); \
  if (jvm_env != NULL) { \
    if (o_ci != NULL) \
      (*jvm_env)->DeleteLocalRef (jvm_env, o_ci); \
    cjni_thread_detach (); \
  } \
  return (status)

  if (jvm == NULL)
  {
    ERROR ("java plugin: cjni_read: jvm == NULL");
    BAIL_OUT (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
  {
    BAIL_OUT (-1);
  }

  /* Find out whether to create a match or a target. */
  if (strcasecmp ("Match", ci->key) == 0)
    type = CB_TYPE_MATCH;
  else if (strcasecmp ("Target", ci->key) == 0)
    type = CB_TYPE_TARGET;
  else
  {
    ERROR ("java plugin: cjni_match_target_create: Can't figure out whether "
        "to create a match or a target.");
    BAIL_OUT (-1);
  }

  /* This is the name of the match we should create. */
  name = ci->values[0].value.string;

  /* Lets see if we have a matching factory here.. */
  cbi_factory = NULL;
  for (i = 0; i < java_callbacks_num; i++)
  {
    if (java_callbacks[i].type != type)
      continue;

    if (strcmp (name, java_callbacks[i].name) != 0)
      continue;

    cbi_factory = java_callbacks + i;
    break;
  }

  /* Nope, no factory for that name.. */
  if (cbi_factory == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: "
        "No such match factory registered: %s",
        name);
    BAIL_OUT (-1);
  }

  /* We convert `ci' to its Java equivalent.. */
  o_ci = ctoj_oconfig_item (jvm_env, ci);
  if (o_ci == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: "
        "ctoj_oconfig_item failed.");
    BAIL_OUT (-1);
  }

  /* Allocate a new callback info structure. This is going to be our user_data
   * pointer. */
  cbi_ret = (cjni_callback_info_t *) malloc (sizeof (*cbi_ret));
  if (cbi_ret == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: malloc failed.");
    BAIL_OUT (-1);
  }
  memset (cbi_ret, 0, sizeof (*cbi_ret));
  cbi_ret->object = NULL;
  cbi_ret->type = type;

  /* Lets fill the callback info structure.. First, the name: */
  cbi_ret->name = strdup (name);
  if (cbi_ret->name == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: strdup failed.");
    BAIL_OUT (-1);
  }

  /* Then call the factory method so it creates a new object for us. */
  o_tmp = (*jvm_env)->CallObjectMethod (jvm_env,
      cbi_factory->object, cbi_factory->method, o_ci);
  if (o_tmp == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: CallObjectMethod failed.");
    BAIL_OUT (-1);
  }

  cbi_ret->object = (*jvm_env)->NewGlobalRef (jvm_env, o_tmp);
  if (o_tmp == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: NewGlobalRef failed.");
    BAIL_OUT (-1);
  }

  /* This is the class of the match. It is possibly different from the class of
   * the match-factory! */
  cbi_ret->class = (*jvm_env)->GetObjectClass (jvm_env, cbi_ret->object);
  if (cbi_ret->class == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: GetObjectClass failed.");
    BAIL_OUT (-1);
  }

  /* Lookup the `int match (DataSet, ValueList)' method. */
  cbi_ret->method = (*jvm_env)->GetMethodID (jvm_env, cbi_ret->class,
      /* method name = */ (type == CB_TYPE_MATCH) ? "match" : "invoke",
      "(Lorg/collectd/api/DataSet;Lorg/collectd/api/ValueList;)I");
  if (cbi_ret->method == NULL)
  {
    ERROR ("java plugin: cjni_match_target_create: GetMethodID failed.");
    BAIL_OUT (-1);
  }

  /* Return the newly created match via the user_data pointer. */
  *user_data = (void *) cbi_ret;

  cjni_thread_detach ();

  DEBUG ("java plugin: cjni_match_target_create: "
      "Successfully created a `%s' %s.",
      cbi_ret->name, (type == CB_TYPE_MATCH) ? "match" : "target");

  /* Success! */
  return (0);
#undef BAIL_OUT
}