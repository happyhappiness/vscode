static int cjni_match_target_invoke (const data_set_t *ds, /* {{{ */
    value_list_t *vl, notification_meta_t **meta, void **user_data)
{
  JNIEnv *jvm_env;
  cjni_callback_info_t *cbi;
  jobject o_vl;
  jobject o_ds;
  int ret_status;
  int status;

  if (jvm == NULL)
  {
    ERROR ("java plugin: cjni_match_target_invoke: jvm == NULL");
    return (-1);
  }

  jvm_env = cjni_thread_attach ();
  if (jvm_env == NULL)
    return (-1);

  cbi = (cjni_callback_info_t *) *user_data;

  o_vl = ctoj_value_list (jvm_env, ds, vl);
  if (o_vl == NULL)
  {
    ERROR ("java plugin: cjni_match_target_invoke: ctoj_value_list failed.");
    cjni_thread_detach ();
    return (-1);
  }

  o_ds = ctoj_data_set (jvm_env, ds);
  if (o_ds == NULL)
  {
    ERROR ("java plugin: cjni_match_target_invoke: ctoj_value_list failed.");
    cjni_thread_detach ();
    return (-1);
  }

  ret_status = (*jvm_env)->CallIntMethod (jvm_env, cbi->object, cbi->method,
      o_ds, o_vl);

  DEBUG ("java plugin: cjni_match_target_invoke: Method returned %i.", ret_status);

  /* If we're executing a target, copy the `ValueList' back to our
   * `value_list_t'. */
  if (cbi->type == CB_TYPE_TARGET)
  {
    value_list_t new_vl = { 0 };

    status = jtoc_value_list (jvm_env, &new_vl, o_vl);
    if (status != 0)
    {
      ERROR ("java plugin: cjni_match_target_invoke: "
          "jtoc_value_list failed.");
    }
    else /* if (status == 0) */
    {
      /* plugin_dispatch_values assures that this is dynamically allocated
       * memory. */
      sfree (vl->values);

      /* This will replace the vl->values pointer to a new, dynamically
       * allocated piece of memory. */
      memcpy (vl, &new_vl, sizeof (*vl));
    }
  } /* if (cbi->type == CB_TYPE_TARGET) */

  cjni_thread_detach ();
  return (ret_status);
}