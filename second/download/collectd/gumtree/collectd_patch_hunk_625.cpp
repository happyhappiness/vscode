   values_num = ds->ds_num;
 
   values = NULL;
   o_number_array = NULL;
   o_list = NULL;
 
-#define BAIL_OUT(status) \
-  free (values); \
-  if (o_number_array != NULL) \
-    (*jvm_env)->DeleteLocalRef (jvm_env, o_number_array); \
-  if (o_list != NULL) \
-    (*jvm_env)->DeleteLocalRef (jvm_env, o_list); \
+#define BAIL_OUT(status)                                                       \
+  free(values);                                                                \
+  if (o_number_array != NULL)                                                  \
+    (*jvm_env)->DeleteLocalRef(jvm_env, o_number_array);                       \
+  if (o_list != NULL)                                                          \
+    (*jvm_env)->DeleteLocalRef(jvm_env, o_list);                               \
   return (status);
 
   /* Call: List<Number> ValueList.getValues () */
-  m_getvalues = (*jvm_env)->GetMethodID (jvm_env, class_ptr,
-      "getValues", "()Ljava/util/List;");
-  if (m_getvalues == NULL)
-  {
-    ERROR ("java plugin: jtoc_values_array: "
-        "Cannot find method `List getValues ()'.");
-    BAIL_OUT (-1);
+  m_getvalues = (*jvm_env)->GetMethodID(jvm_env, class_ptr, "getValues",
+                                        "()Ljava/util/List;");
+  if (m_getvalues == NULL) {
+    ERROR("java plugin: jtoc_values_array: "
+          "Cannot find method `List getValues ()'.");
+    BAIL_OUT(-1);
   }
 
-  o_list = (*jvm_env)->CallObjectMethod (jvm_env, object_ptr, m_getvalues);
-  if (o_list == NULL)
-  {
-    ERROR ("java plugin: jtoc_values_array: "
-        "CallObjectMethod (getValues) failed.");
-    BAIL_OUT (-1);
+  o_list = (*jvm_env)->CallObjectMethod(jvm_env, object_ptr, m_getvalues);
+  if (o_list == NULL) {
+    ERROR("java plugin: jtoc_values_array: "
+          "CallObjectMethod (getValues) failed.");
+    BAIL_OUT(-1);
   }
 
   /* Call: Number[] List.toArray () */
-  m_toarray = (*jvm_env)->GetMethodID (jvm_env,
-      (*jvm_env)->GetObjectClass (jvm_env, o_list),
-      "toArray", "()[Ljava/lang/Object;");
-  if (m_toarray == NULL)
-  {
-    ERROR ("java plugin: jtoc_values_array: "
-        "Cannot find method `Object[] toArray ()'.");
-    BAIL_OUT (-1);
+  m_toarray = (*jvm_env)->GetMethodID(
+      jvm_env, (*jvm_env)->GetObjectClass(jvm_env, o_list), "toArray",
+      "()[Ljava/lang/Object;");
+  if (m_toarray == NULL) {
+    ERROR("java plugin: jtoc_values_array: "
+          "Cannot find method `Object[] toArray ()'.");
+    BAIL_OUT(-1);
   }
 
-  o_number_array = (*jvm_env)->CallObjectMethod (jvm_env, o_list, m_toarray);
-  if (o_number_array == NULL)
-  {
-    ERROR ("java plugin: jtoc_values_array: "
-        "CallObjectMethod (toArray) failed.");
-    BAIL_OUT (-1);
+  o_number_array = (*jvm_env)->CallObjectMethod(jvm_env, o_list, m_toarray);
+  if (o_number_array == NULL) {
+    ERROR("java plugin: jtoc_values_array: "
+          "CallObjectMethod (toArray) failed.");
+    BAIL_OUT(-1);
   }
 
-  values = (value_t *) calloc (values_num, sizeof (value_t));
-  if (values == NULL)
-  {
-    ERROR ("java plugin: jtoc_values_array: calloc failed.");
-    BAIL_OUT (-1);
+  values = (value_t *)calloc(values_num, sizeof(value_t));
+  if (values == NULL) {
+    ERROR("java plugin: jtoc_values_array: calloc failed.");
+    BAIL_OUT(-1);
   }
 
-  for (int i = 0; i < values_num; i++)
-  {
+  for (int i = 0; i < values_num; i++) {
     jobject o_number;
     int status;
 
-    o_number = (*jvm_env)->GetObjectArrayElement (jvm_env,
-        o_number_array, (jsize) i);
-    if (o_number == NULL)
-    {
-      ERROR ("java plugin: jtoc_values_array: "
-          "GetObjectArrayElement (%i) failed.", i);
-      BAIL_OUT (-1);
+    o_number =
+        (*jvm_env)->GetObjectArrayElement(jvm_env, o_number_array, (jsize)i);
+    if (o_number == NULL) {
+      ERROR("java plugin: jtoc_values_array: "
+            "GetObjectArrayElement (%i) failed.",
+            i);
+      BAIL_OUT(-1);
     }
 
-    status = jtoc_value (jvm_env, values + i, ds->ds[i].type, o_number);
-    if (status != 0)
-    {
-      ERROR ("java plugin: jtoc_values_array: "
-          "jtoc_value (%i) failed.", i);
-      BAIL_OUT (-1);
+    status = jtoc_value(jvm_env, values + i, ds->ds[i].type, o_number);
+    if (status != 0) {
+      ERROR("java plugin: jtoc_values_array: "
+            "jtoc_value (%i) failed.",
+            i);
+      BAIL_OUT(-1);
     }
   } /* for (i = 0; i < values_num; i++) */
 
   vl->values = values;
   vl->values_len = values_num;
 
 #undef BAIL_OUT
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_number_array);
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_list);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_number_array);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_list);
   return (0);
 } /* }}} int jtoc_values_array */
 
 /* Convert a org/collectd/api/ValueList to a value_list_t. */
-static int jtoc_value_list (JNIEnv *jvm_env, value_list_t *vl, /* {{{ */
-    jobject object_ptr)
-{
+static int jtoc_value_list(JNIEnv *jvm_env, value_list_t *vl, /* {{{ */
+                           jobject object_ptr) {
   jclass class_ptr;
   int status;
   jlong tmp_long;
   const data_set_t *ds;
 
-  class_ptr = (*jvm_env)->GetObjectClass (jvm_env, object_ptr);
-  if (class_ptr == NULL)
-  {
-    ERROR ("java plugin: jtoc_value_list: GetObjectClass failed.");
+  class_ptr = (*jvm_env)->GetObjectClass(jvm_env, object_ptr);
+  if (class_ptr == NULL) {
+    ERROR("java plugin: jtoc_value_list: GetObjectClass failed.");
     return (-1);
   }
 
-  /* eo == empty okay */
-#define SET_STRING(buffer,method, eo) do { \
-  status = jtoc_string (jvm_env, buffer, sizeof (buffer), eo, \
-      class_ptr, object_ptr, method); \
-  if (status != 0) { \
-    ERROR ("java plugin: jtoc_value_list: jtoc_string (%s) failed.", \
-        method); \
-    return (-1); \
-  } } while (0)
+/* eo == empty okay */
+#define SET_STRING(buffer, method, eo)                                         \
+  do {                                                                         \
+    status = jtoc_string(jvm_env, buffer, sizeof(buffer), eo, class_ptr,       \
+                         object_ptr, method);                                  \
+    if (status != 0) {                                                         \
+      ERROR("java plugin: jtoc_value_list: jtoc_string (%s) failed.", method); \
+      return (-1);                                                             \
+    }                                                                          \
+  } while (0)
 
   SET_STRING(vl->type, "getType", /* empty = */ 0);
 
-  ds = plugin_get_ds (vl->type);
-  if (ds == NULL)
-  {
-    ERROR ("java plugin: jtoc_value_list: Data-set `%s' is not defined. "
-        "Please consult the types.db(5) manpage for mor information.",
-        vl->type);
+  ds = plugin_get_ds(vl->type);
+  if (ds == NULL) {
+    ERROR("java plugin: jtoc_value_list: Data-set `%s' is not defined. "
+          "Please consult the types.db(5) manpage for mor information.",
+          vl->type);
     return (-1);
   }
 
-  SET_STRING(vl->host,            "getHost",           /* empty = */ 0);
-  SET_STRING(vl->plugin,          "getPlugin",         /* empty = */ 0);
+  SET_STRING(vl->host, "getHost", /* empty = */ 0);
+  SET_STRING(vl->plugin, "getPlugin", /* empty = */ 0);
   SET_STRING(vl->plugin_instance, "getPluginInstance", /* empty = */ 1);
-  SET_STRING(vl->type_instance,   "getTypeInstance",   /* empty = */ 1);
+  SET_STRING(vl->type_instance, "getTypeInstance", /* empty = */ 1);
 
 #undef SET_STRING
 
-  status = jtoc_long (jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
-  if (status != 0)
-  {
-    ERROR ("java plugin: jtoc_value_list: jtoc_long (getTime) failed.");
+  status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
+  if (status != 0) {
+    ERROR("java plugin: jtoc_value_list: jtoc_long (getTime) failed.");
     return (-1);
   }
   /* Java measures time in milliseconds. */
-  vl->time = MS_TO_CDTIME_T (tmp_long);
+  vl->time = MS_TO_CDTIME_T(tmp_long);
 
-  status = jtoc_long (jvm_env, &tmp_long,
-      class_ptr, object_ptr, "getInterval");
-  if (status != 0)
-  {
-    ERROR ("java plugin: jtoc_value_list: jtoc_long (getInterval) failed.");
+  status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "getInterval");
+  if (status != 0) {
+    ERROR("java plugin: jtoc_value_list: jtoc_long (getInterval) failed.");
     return (-1);
   }
-  vl->interval = MS_TO_CDTIME_T (tmp_long);
+  vl->interval = MS_TO_CDTIME_T(tmp_long);
 
-  status = jtoc_values_array (jvm_env, ds, vl, class_ptr, object_ptr);
-  if (status != 0)
-  {
-    ERROR ("java plugin: jtoc_value_list: jtoc_values_array failed.");
+  status = jtoc_values_array(jvm_env, ds, vl, class_ptr, object_ptr);
+  if (status != 0) {
+    ERROR("java plugin: jtoc_value_list: jtoc_values_array failed.");
     return (-1);
   }
 
   return (0);
 } /* }}} int jtoc_value_list */
 
 /* Convert a org/collectd/api/Notification to a notification_t. */
-static int jtoc_notification (JNIEnv *jvm_env, notification_t *n, /* {{{ */
-    jobject object_ptr)
-{
+static int jtoc_notification(JNIEnv *jvm_env, notification_t *n, /* {{{ */
+                             jobject object_ptr) {
   jclass class_ptr;
   int status;
   jlong tmp_long;
   jint tmp_int;
 
-  class_ptr = (*jvm_env)->GetObjectClass (jvm_env, object_ptr);
-  if (class_ptr == NULL)
-  {
-    ERROR ("java plugin: jtoc_notification: GetObjectClass failed.");
+  class_ptr = (*jvm_env)->GetObjectClass(jvm_env, object_ptr);
+  if (class_ptr == NULL) {
+    ERROR("java plugin: jtoc_notification: GetObjectClass failed.");
     return (-1);
   }
 
-  /* eo == empty okay */
-#define SET_STRING(buffer,method, eo) do { \
-  status = jtoc_string (jvm_env, buffer, sizeof (buffer), eo, \
-      class_ptr, object_ptr, method); \
-  if (status != 0) { \
-    ERROR ("java plugin: jtoc_notification: jtoc_string (%s) failed.", \
-        method); \
-    return (-1); \
-  } } while (0)
-
-  SET_STRING (n->host,            "getHost",           /* empty = */ 1);
-  SET_STRING (n->plugin,          "getPlugin",         /* empty = */ 1);
-  SET_STRING (n->plugin_instance, "getPluginInstance", /* empty = */ 1);
-  SET_STRING (n->type,            "getType",           /* empty = */ 1);
-  SET_STRING (n->type_instance,   "getTypeInstance",   /* empty = */ 1);
-  SET_STRING (n->message,         "getMessage",        /* empty = */ 0);
+/* eo == empty okay */
+#define SET_STRING(buffer, method, eo)                                         \
+  do {                                                                         \
+    status = jtoc_string(jvm_env, buffer, sizeof(buffer), eo, class_ptr,       \
+                         object_ptr, method);                                  \
+    if (status != 0) {                                                         \
+      ERROR("java plugin: jtoc_notification: jtoc_string (%s) failed.",        \
+            method);                                                           \
+      return (-1);                                                             \
+    }                                                                          \
+  } while (0)
+
+  SET_STRING(n->host, "getHost", /* empty = */ 1);
+  SET_STRING(n->plugin, "getPlugin", /* empty = */ 1);
+  SET_STRING(n->plugin_instance, "getPluginInstance", /* empty = */ 1);
+  SET_STRING(n->type, "getType", /* empty = */ 1);
+  SET_STRING(n->type_instance, "getTypeInstance", /* empty = */ 1);
+  SET_STRING(n->message, "getMessage", /* empty = */ 0);
 
 #undef SET_STRING
 
-  status = jtoc_long (jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
-  if (status != 0)
-  {
-    ERROR ("java plugin: jtoc_notification: jtoc_long (getTime) failed.");
+  status = jtoc_long(jvm_env, &tmp_long, class_ptr, object_ptr, "getTime");
+  if (status != 0) {
+    ERROR("java plugin: jtoc_notification: jtoc_long (getTime) failed.");
     return (-1);
   }
   /* Java measures time in milliseconds. */
   n->time = MS_TO_CDTIME_T(tmp_long);
 
-  status = jtoc_int (jvm_env, &tmp_int,
-      class_ptr, object_ptr, "getSeverity");
-  if (status != 0)
-  {
-    ERROR ("java plugin: jtoc_notification: jtoc_int (getSeverity) failed.");
+  status = jtoc_int(jvm_env, &tmp_int, class_ptr, object_ptr, "getSeverity");
+  if (status != 0) {
+    ERROR("java plugin: jtoc_notification: jtoc_int (getSeverity) failed.");
     return (-1);
   }
-  n->severity = (int) tmp_int;
+  n->severity = (int)tmp_int;
 
   return (0);
 } /* }}} int jtoc_notification */
-/*
- * Functions accessible from Java
- */
-static jint JNICALL cjni_api_dispatch_values (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject java_vl)
-{
+  /*
+   * Functions accessible from Java
+   */
+static jint JNICALL cjni_api_dispatch_values(JNIEnv *jvm_env, /* {{{ */
+                                             jobject this, jobject java_vl) {
   value_list_t vl = VALUE_LIST_INIT;
   int status;
 
-  DEBUG ("cjni_api_dispatch_values: java_vl = %p;", (void *) java_vl);
+  DEBUG("cjni_api_dispatch_values: java_vl = %p;", (void *)java_vl);
 
-  status = jtoc_value_list (jvm_env, &vl, java_vl);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_api_dispatch_values: jtoc_value_list failed.");
+  status = jtoc_value_list(jvm_env, &vl, java_vl);
+  if (status != 0) {
+    ERROR("java plugin: cjni_api_dispatch_values: jtoc_value_list failed.");
     return (-1);
   }
 
-  status = plugin_dispatch_values (&vl);
+  status = plugin_dispatch_values(&vl);
 
-  sfree (vl.values);
+  sfree(vl.values);
 
   return (status);
 } /* }}} jint cjni_api_dispatch_values */
 
-static jint JNICALL cjni_api_dispatch_notification (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_notification)
-{
-  notification_t n = { 0 };
+static jint JNICALL cjni_api_dispatch_notification(JNIEnv *jvm_env, /* {{{ */
+                                                   jobject this,
+                                                   jobject o_notification) {
+  notification_t n = {0};
   int status;
 
-  status = jtoc_notification (jvm_env, &n, o_notification);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_api_dispatch_notification: jtoc_notification failed.");
+  status = jtoc_notification(jvm_env, &n, o_notification);
+  if (status != 0) {
+    ERROR("java plugin: cjni_api_dispatch_notification: jtoc_notification "
+          "failed.");
     return (-1);
   }
 
-  status = plugin_dispatch_notification (&n);
+  status = plugin_dispatch_notification(&n);
 
   return (status);
 } /* }}} jint cjni_api_dispatch_notification */
 
-static jobject JNICALL cjni_api_get_ds (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_string_type)
-{
+static jobject JNICALL cjni_api_get_ds(JNIEnv *jvm_env, /* {{{ */
+                                       jobject this, jobject o_string_type) {
   const char *ds_name;
   const data_set_t *ds;
   jobject o_dataset;
 
-  ds_name = (*jvm_env)->GetStringUTFChars (jvm_env, o_string_type, 0);
-  if (ds_name == NULL)
-  {
-    ERROR ("java plugin: cjni_api_get_ds: GetStringUTFChars failed.");
+  ds_name = (*jvm_env)->GetStringUTFChars(jvm_env, o_string_type, 0);
+  if (ds_name == NULL) {
+    ERROR("java plugin: cjni_api_get_ds: GetStringUTFChars failed.");
     return (NULL);
   }
 
-  ds = plugin_get_ds (ds_name);
-  DEBUG ("java plugin: cjni_api_get_ds: "
-      "plugin_get_ds (%s) = %p;", ds_name, (void *) ds);
+  ds = plugin_get_ds(ds_name);
+  DEBUG("java plugin: cjni_api_get_ds: "
+        "plugin_get_ds (%s) = %p;",
+        ds_name, (void *)ds);
 
-  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_string_type, ds_name);
+  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_string_type, ds_name);
 
   if (ds == NULL)
     return (NULL);
 
-  o_dataset = ctoj_data_set (jvm_env, ds);
+  o_dataset = ctoj_data_set(jvm_env, ds);
   return (o_dataset);
 } /* }}} jint cjni_api_get_ds */
 
-static jint JNICALL cjni_api_register_config (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_config)
-{
-  return (cjni_callback_register (jvm_env, o_name, o_config, CB_TYPE_CONFIG));
+static jint JNICALL cjni_api_register_config(JNIEnv *jvm_env, /* {{{ */
+                                             jobject this, jobject o_name,
+                                             jobject o_config) {
+  return (cjni_callback_register(jvm_env, o_name, o_config, CB_TYPE_CONFIG));
 } /* }}} jint cjni_api_register_config */
 
-static jint JNICALL cjni_api_register_init (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_config)
-{
-  return (cjni_callback_register (jvm_env, o_name, o_config, CB_TYPE_INIT));
+static jint JNICALL cjni_api_register_init(JNIEnv *jvm_env, /* {{{ */
+                                           jobject this, jobject o_name,
+                                           jobject o_config) {
+  return (cjni_callback_register(jvm_env, o_name, o_config, CB_TYPE_INIT));
 } /* }}} jint cjni_api_register_init */
 
-static jint JNICALL cjni_api_register_read (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_read)
-{
+static jint JNICALL cjni_api_register_read(JNIEnv *jvm_env, /* {{{ */
+                                           jobject this, jobject o_name,
+                                           jobject o_read) {
   cjni_callback_info_t *cbi;
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_read, CB_TYPE_READ);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_read, CB_TYPE_READ);
   if (cbi == NULL)
     return (-1);
 
-  DEBUG ("java plugin: Registering new read callback: %s", cbi->name);
+  DEBUG("java plugin: Registering new read callback: %s", cbi->name);
 
-  user_data_t ud = {
-    .data = cbi,
-    .free_func = cjni_callback_info_destroy
-  };
+  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};
 
-  plugin_register_complex_read (/* group = */ NULL, cbi->name, cjni_read,
-      /* interval = */ 0, &ud);
+  plugin_register_complex_read(/* group = */ NULL, cbi->name, cjni_read,
+                               /* interval = */ 0, &ud);
 
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_read);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_read);
 
   return (0);
 } /* }}} jint cjni_api_register_read */
 
-static jint JNICALL cjni_api_register_write (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_write)
-{
+static jint JNICALL cjni_api_register_write(JNIEnv *jvm_env, /* {{{ */
+                                            jobject this, jobject o_name,
+                                            jobject o_write) {
   cjni_callback_info_t *cbi;
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_write, CB_TYPE_WRITE);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_write, CB_TYPE_WRITE);
   if (cbi == NULL)
     return (-1);
 
-  DEBUG ("java plugin: Registering new write callback: %s", cbi->name);
+  DEBUG("java plugin: Registering new write callback: %s", cbi->name);
 
-  user_data_t ud = {
-    .data = cbi,
-    .free_func = cjni_callback_info_destroy
-  };
+  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};
 
-  plugin_register_write (cbi->name, cjni_write, &ud);
+  plugin_register_write(cbi->name, cjni_write, &ud);
 
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_write);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_write);
 
   return (0);
 } /* }}} jint cjni_api_register_write */
 
-static jint JNICALL cjni_api_register_flush (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_flush)
-{
+static jint JNICALL cjni_api_register_flush(JNIEnv *jvm_env, /* {{{ */
+                                            jobject this, jobject o_name,
+                                            jobject o_flush) {
   cjni_callback_info_t *cbi;
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_flush, CB_TYPE_FLUSH);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_flush, CB_TYPE_FLUSH);
   if (cbi == NULL)
     return (-1);
 
-  DEBUG ("java plugin: Registering new flush callback: %s", cbi->name);
+  DEBUG("java plugin: Registering new flush callback: %s", cbi->name);
 
-  user_data_t ud = {
-    .data = cbi,
-    .free_func = cjni_callback_info_destroy
-  };
+  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};
 
-  plugin_register_flush (cbi->name, cjni_flush, &ud);
+  plugin_register_flush(cbi->name, cjni_flush, &ud);
 
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_flush);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_flush);
 
   return (0);
 } /* }}} jint cjni_api_register_flush */
 
-static jint JNICALL cjni_api_register_shutdown (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_shutdown)
-{
-  return (cjni_callback_register (jvm_env, o_name, o_shutdown,
-        CB_TYPE_SHUTDOWN));
+static jint JNICALL cjni_api_register_shutdown(JNIEnv *jvm_env, /* {{{ */
+                                               jobject this, jobject o_name,
+                                               jobject o_shutdown) {
+  return (
+      cjni_callback_register(jvm_env, o_name, o_shutdown, CB_TYPE_SHUTDOWN));
 } /* }}} jint cjni_api_register_shutdown */
 
-static jint JNICALL cjni_api_register_log (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_log)
-{
+static jint JNICALL cjni_api_register_log(JNIEnv *jvm_env, /* {{{ */
+                                          jobject this, jobject o_name,
+                                          jobject o_log) {
   cjni_callback_info_t *cbi;
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_log, CB_TYPE_LOG);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_log, CB_TYPE_LOG);
   if (cbi == NULL)
     return (-1);
 
-  DEBUG ("java plugin: Registering new log callback: %s", cbi->name);
+  DEBUG("java plugin: Registering new log callback: %s", cbi->name);
 
-  user_data_t ud = {
-    .data = cbi,
-    .free_func = cjni_callback_info_destroy
-  };
+  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};
 
-  plugin_register_log (cbi->name, cjni_log, &ud);
+  plugin_register_log(cbi->name, cjni_log, &ud);
 
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_log);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_log);
 
   return (0);
 } /* }}} jint cjni_api_register_log */
 
-static jint JNICALL cjni_api_register_notification (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_notification)
-{
+static jint JNICALL cjni_api_register_notification(JNIEnv *jvm_env, /* {{{ */
+                                                   jobject this, jobject o_name,
+                                                   jobject o_notification) {
   cjni_callback_info_t *cbi;
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_notification,
-      CB_TYPE_NOTIFICATION);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_notification,
+                                  CB_TYPE_NOTIFICATION);
   if (cbi == NULL)
     return (-1);
 
-  DEBUG ("java plugin: Registering new notification callback: %s", cbi->name);
+  DEBUG("java plugin: Registering new notification callback: %s", cbi->name);
 
-  user_data_t ud = {
-    .data = cbi,
-    .free_func = cjni_callback_info_destroy
-  };
+  user_data_t ud = {.data = cbi, .free_func = cjni_callback_info_destroy};
 
-  plugin_register_notification (cbi->name, cjni_notification, &ud);
+  plugin_register_notification(cbi->name, cjni_notification, &ud);
 
-  (*jvm_env)->DeleteLocalRef (jvm_env, o_notification);
+  (*jvm_env)->DeleteLocalRef(jvm_env, o_notification);
 
   return (0);
 } /* }}} jint cjni_api_register_notification */
 
-static jint JNICALL cjni_api_register_match_target (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_match, int type)
-{
+static jint JNICALL cjni_api_register_match_target(JNIEnv *jvm_env, /* {{{ */
+                                                   jobject this, jobject o_name,
+                                                   jobject o_match, int type) {
   int status;
   const char *c_name;
 
-  c_name = (*jvm_env)->GetStringUTFChars (jvm_env, o_name, 0);
-  if (c_name == NULL)
-  {
-    ERROR ("java plugin: cjni_api_register_match_target: "
-        "GetStringUTFChars failed.");
+  c_name = (*jvm_env)->GetStringUTFChars(jvm_env, o_name, 0);
+  if (c_name == NULL) {
+    ERROR("java plugin: cjni_api_register_match_target: "
+          "GetStringUTFChars failed.");
     return (-1);
   }
 
-  status = cjni_callback_register (jvm_env, o_name, o_match, type);
-  if (status != 0)
-  {
-    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+  status = cjni_callback_register(jvm_env, o_name, o_match, type);
+  if (status != 0) {
+    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
     return (-1);
   }
 
-  if (type == CB_TYPE_MATCH)
-  {
-    match_proc_t m_proc = { 0 };
+  if (type == CB_TYPE_MATCH) {
+    match_proc_t m_proc = {0};
 
-    m_proc.create  = cjni_match_target_create;
+    m_proc.create = cjni_match_target_create;
     m_proc.destroy = cjni_match_target_destroy;
-    m_proc.match   = (void *) cjni_match_target_invoke;
+    m_proc.match = (void *)cjni_match_target_invoke;
 
-    status = fc_register_match (c_name, m_proc);
-  }
-  else if (type == CB_TYPE_TARGET)
-  {
-    target_proc_t t_proc = { 0 };
+    status = fc_register_match(c_name, m_proc);
+  } else if (type == CB_TYPE_TARGET) {
+    target_proc_t t_proc = {0};
 
-    t_proc.create  = cjni_match_target_create;
+    t_proc.create = cjni_match_target_create;
     t_proc.destroy = cjni_match_target_destroy;
-    t_proc.invoke  = cjni_match_target_invoke;
+    t_proc.invoke = cjni_match_target_invoke;
 
-    status = fc_register_target (c_name, t_proc);
-  }
-  else
-  {
-    ERROR ("java plugin: cjni_api_register_match_target: "
-        "Don't know whether to create a match or a target.");
-    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+    status = fc_register_target(c_name, t_proc);
+  } else {
+    ERROR("java plugin: cjni_api_register_match_target: "
+          "Don't know whether to create a match or a target.");
+    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
     return (-1);
   }
 
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_api_register_match_target: "
-        "%s failed.",
-        (type == CB_TYPE_MATCH) ? "fc_register_match" : "fc_register_target");
-    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+  if (status != 0) {
+    ERROR("java plugin: cjni_api_register_match_target: "
+          "%s failed.",
+          (type == CB_TYPE_MATCH) ? "fc_register_match" : "fc_register_target");
+    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
     return (-1);
   }
 
-  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
 
   return (0);
 } /* }}} jint cjni_api_register_match_target */
 
-static jint JNICALL cjni_api_register_match (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_match)
-{
-  return (cjni_api_register_match_target (jvm_env, this, o_name, o_match,
-        CB_TYPE_MATCH));
+static jint JNICALL cjni_api_register_match(JNIEnv *jvm_env, /* {{{ */
+                                            jobject this, jobject o_name,
+                                            jobject o_match) {
+  return (cjni_api_register_match_target(jvm_env, this, o_name, o_match,
+                                         CB_TYPE_MATCH));
 } /* }}} jint cjni_api_register_match */
 
-static jint JNICALL cjni_api_register_target (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jobject o_name, jobject o_target)
-{
-  return (cjni_api_register_match_target (jvm_env, this, o_name, o_target,
-        CB_TYPE_TARGET));
+static jint JNICALL cjni_api_register_target(JNIEnv *jvm_env, /* {{{ */
+                                             jobject this, jobject o_name,
+                                             jobject o_target) {
+  return (cjni_api_register_match_target(jvm_env, this, o_name, o_target,
+                                         CB_TYPE_TARGET));
 } /* }}} jint cjni_api_register_target */
 
-static void JNICALL cjni_api_log (JNIEnv *jvm_env, /* {{{ */
-    jobject this, jint severity, jobject o_message)
-{
+static void JNICALL cjni_api_log(JNIEnv *jvm_env, /* {{{ */
+                                 jobject this, jint severity,
+                                 jobject o_message) {
   const char *c_str;
 
-  c_str = (*jvm_env)->GetStringUTFChars (jvm_env, o_message, 0);
-  if (c_str == NULL)
-  {
-    ERROR ("java plugin: cjni_api_log: GetStringUTFChars failed.");
+  c_str = (*jvm_env)->GetStringUTFChars(jvm_env, o_message, 0);
+  if (c_str == NULL) {
+    ERROR("java plugin: cjni_api_log: GetStringUTFChars failed.");
     return;
   }
 
   if (severity < LOG_ERR)
     severity = LOG_ERR;
   if (severity > LOG_DEBUG)
     severity = LOG_DEBUG;
 
-  plugin_log (severity, "%s", c_str);
+  plugin_log(severity, "%s", c_str);
 
-  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_message, c_str);
+  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_message, c_str);
 } /* }}} void cjni_api_log */
 
-static jstring JNICALL cjni_api_get_hostname (JNIEnv *jvm_env, jobject this)
-{
-    return ctoj_output_string(jvm_env, hostname_g);
+static jstring JNICALL cjni_api_get_hostname(JNIEnv *jvm_env, jobject this) {
+  return ctoj_output_string(jvm_env, hostname_g);
 }
 
 /* List of ``native'' functions, i. e. C-functions that can be called from
  * Java. */
 static JNINativeMethod jni_api_functions[] = /* {{{ */
-{
-  { "dispatchValues",
-    "(Lorg/collectd/api/ValueList;)I",
-    cjni_api_dispatch_values },
-
-  { "dispatchNotification",
-    "(Lorg/collectd/api/Notification;)I",
-    cjni_api_dispatch_notification },
-
-  { "getDS",
-    "(Ljava/lang/String;)Lorg/collectd/api/DataSet;",
-    cjni_api_get_ds },
-
-  { "registerConfig",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdConfigInterface;)I",
-    cjni_api_register_config },
-
-  { "registerInit",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdInitInterface;)I",
-    cjni_api_register_init },
-
-  { "registerRead",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdReadInterface;)I",
-    cjni_api_register_read },
-
-  { "registerWrite",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdWriteInterface;)I",
-    cjni_api_register_write },
-
-  { "registerFlush",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdFlushInterface;)I",
-    cjni_api_register_flush },
-
-  { "registerShutdown",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdShutdownInterface;)I",
-    cjni_api_register_shutdown },
-
-  { "registerLog",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdLogInterface;)I",
-    cjni_api_register_log },
-
-  { "registerNotification",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdNotificationInterface;)I",
-    cjni_api_register_notification },
-
-  { "registerMatch",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdMatchFactoryInterface;)I",
-    cjni_api_register_match },
-
-  { "registerTarget",
-    "(Ljava/lang/String;Lorg/collectd/api/CollectdTargetFactoryInterface;)I",
-    cjni_api_register_target },
-
-  { "log",
-    "(ILjava/lang/String;)V",
-    cjni_api_log },
-
-  { "getHostname",
-    "()Ljava/lang/String;",
-    cjni_api_get_hostname },
+    {
+        {"dispatchValues", "(Lorg/collectd/api/ValueList;)I",
+         cjni_api_dispatch_values},
+
+        {"dispatchNotification", "(Lorg/collectd/api/Notification;)I",
+         cjni_api_dispatch_notification},
+
+        {"getDS", "(Ljava/lang/String;)Lorg/collectd/api/DataSet;",
+         cjni_api_get_ds},
+
+        {"registerConfig",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdConfigInterface;)I",
+         cjni_api_register_config},
+
+        {"registerInit",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdInitInterface;)I",
+         cjni_api_register_init},
+
+        {"registerRead",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdReadInterface;)I",
+         cjni_api_register_read},
+
+        {"registerWrite",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdWriteInterface;)I",
+         cjni_api_register_write},
+
+        {"registerFlush",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdFlushInterface;)I",
+         cjni_api_register_flush},
+
+        {"registerShutdown",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdShutdownInterface;)I",
+         cjni_api_register_shutdown},
+
+        {"registerLog",
+         "(Ljava/lang/String;Lorg/collectd/api/CollectdLogInterface;)I",
+         cjni_api_register_log},
+
+        {"registerNotification", "(Ljava/lang/String;Lorg/collectd/api/"
+                                 "CollectdNotificationInterface;)I",
+         cjni_api_register_notification},
+
+        {"registerMatch", "(Ljava/lang/String;Lorg/collectd/api/"
+                          "CollectdMatchFactoryInterface;)I",
+         cjni_api_register_match},
+
+        {"registerTarget", "(Ljava/lang/String;Lorg/collectd/api/"
+                           "CollectdTargetFactoryInterface;)I",
+         cjni_api_register_target},
+
+        {"log", "(ILjava/lang/String;)V", cjni_api_log},
+
+        {"getHostname", "()Ljava/lang/String;", cjni_api_get_hostname},
 
 };
-static size_t jni_api_functions_num = sizeof (jni_api_functions)
-  / sizeof (jni_api_functions[0]);
+static size_t jni_api_functions_num =
+    sizeof(jni_api_functions) / sizeof(jni_api_functions[0]);
 /* }}} */
 
 /*
  * Functions
  */
 /* Allocate a `cjni_callback_info_t' given the type and objects necessary for
  * all registration functions. */
-static cjni_callback_info_t *cjni_callback_info_create (JNIEnv *jvm_env, /* {{{ */
-    jobject o_name, jobject o_callback, int type)
-{
+static cjni_callback_info_t *
+cjni_callback_info_create(JNIEnv *jvm_env, /* {{{ */
+                          jobject o_name, jobject o_callback, int type) {
   const char *c_name;
   cjni_callback_info_t *cbi;
   const char *method_name;
   const char *method_signature;
 
-  switch (type)
-  {
-    case CB_TYPE_CONFIG:
-      method_name = "config";
-      method_signature = "(Lorg/collectd/api/OConfigItem;)I";
-      break;
-
-    case CB_TYPE_INIT:
-      method_name = "init";
-      method_signature = "()I";
-      break;
-
-    case CB_TYPE_READ:
-      method_name = "read";
-      method_signature = "()I";
-      break;
-
-    case CB_TYPE_WRITE:
-      method_name = "write";
-      method_signature = "(Lorg/collectd/api/ValueList;)I";
-      break;
-
-    case CB_TYPE_FLUSH:
-      method_name = "flush";
-      method_signature = "(Ljava/lang/Number;Ljava/lang/String;)I";
-      break;
-
-    case CB_TYPE_SHUTDOWN:
-      method_name = "shutdown";
-      method_signature = "()I";
-      break;
-
-    case CB_TYPE_LOG:
-      method_name = "log";
-      method_signature = "(ILjava/lang/String;)V";
-      break;
-
-    case CB_TYPE_NOTIFICATION:
-      method_name = "notification";
-      method_signature = "(Lorg/collectd/api/Notification;)I";
-      break;
-
-    case CB_TYPE_MATCH:
-      method_name = "createMatch";
-      method_signature = "(Lorg/collectd/api/OConfigItem;)"
-        "Lorg/collectd/api/CollectdMatchInterface;";
-      break;
-
-    case CB_TYPE_TARGET:
-      method_name = "createTarget";
-      method_signature = "(Lorg/collectd/api/OConfigItem;)"
-        "Lorg/collectd/api/CollectdTargetInterface;";
-      break;
-
-    default:
-      ERROR ("java plugin: cjni_callback_info_create: Unknown type: %#x",
-          type);
-      return (NULL);
+  switch (type) {
+  case CB_TYPE_CONFIG:
+    method_name = "config";
+    method_signature = "(Lorg/collectd/api/OConfigItem;)I";
+    break;
+
+  case CB_TYPE_INIT:
+    method_name = "init";
+    method_signature = "()I";
+    break;
+
+  case CB_TYPE_READ:
+    method_name = "read";
+    method_signature = "()I";
+    break;
+
+  case CB_TYPE_WRITE:
+    method_name = "write";
+    method_signature = "(Lorg/collectd/api/ValueList;)I";
+    break;
+
+  case CB_TYPE_FLUSH:
+    method_name = "flush";
+    method_signature = "(Ljava/lang/Number;Ljava/lang/String;)I";
+    break;
+
+  case CB_TYPE_SHUTDOWN:
+    method_name = "shutdown";
+    method_signature = "()I";
+    break;
+
+  case CB_TYPE_LOG:
+    method_name = "log";
+    method_signature = "(ILjava/lang/String;)V";
+    break;
+
+  case CB_TYPE_NOTIFICATION:
+    method_name = "notification";
+    method_signature = "(Lorg/collectd/api/Notification;)I";
+    break;
+
+  case CB_TYPE_MATCH:
+    method_name = "createMatch";
+    method_signature = "(Lorg/collectd/api/OConfigItem;)"
+                       "Lorg/collectd/api/CollectdMatchInterface;";
+    break;
+
+  case CB_TYPE_TARGET:
+    method_name = "createTarget";
+    method_signature = "(Lorg/collectd/api/OConfigItem;)"
+                       "Lorg/collectd/api/CollectdTargetInterface;";
+    break;
+
+  default:
+    ERROR("java plugin: cjni_callback_info_create: Unknown type: %#x", type);
+    return (NULL);
   }
 
-  c_name = (*jvm_env)->GetStringUTFChars (jvm_env, o_name, 0);
-  if (c_name == NULL)
-  {
-    ERROR ("java plugin: cjni_callback_info_create: "
-        "GetStringUTFChars failed.");
+  c_name = (*jvm_env)->GetStringUTFChars(jvm_env, o_name, 0);
+  if (c_name == NULL) {
+    ERROR("java plugin: cjni_callback_info_create: "
+          "GetStringUTFChars failed.");
     return (NULL);
   }
 
-  cbi = calloc (1, sizeof (*cbi));
-  if (cbi == NULL)
-  {
-    ERROR ("java plugin: cjni_callback_info_create: calloc failed.");
-    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+  cbi = calloc(1, sizeof(*cbi));
+  if (cbi == NULL) {
+    ERROR("java plugin: cjni_callback_info_create: calloc failed.");
+    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
     return (NULL);
   }
   cbi->type = type;
 
-  cbi->name = strdup (c_name);
-  if (cbi->name == NULL)
-  {
-    pthread_mutex_unlock (&java_callbacks_lock);
-    ERROR ("java plugin: cjni_callback_info_create: strdup failed.");
-    (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
-    sfree (cbi);
+  cbi->name = strdup(c_name);
+  if (cbi->name == NULL) {
+    pthread_mutex_unlock(&java_callbacks_lock);
+    ERROR("java plugin: cjni_callback_info_create: strdup failed.");
+    (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
+    sfree(cbi);
     return (NULL);
   }
 
-  (*jvm_env)->ReleaseStringUTFChars (jvm_env, o_name, c_name);
+  (*jvm_env)->ReleaseStringUTFChars(jvm_env, o_name, c_name);
 
-  cbi->object = (*jvm_env)->NewGlobalRef (jvm_env, o_callback);
-  if (cbi->object == NULL)
-  {
-    ERROR ("java plugin: cjni_callback_info_create: NewGlobalRef failed.");
-    sfree (cbi->name);
-    sfree (cbi);
+  cbi->object = (*jvm_env)->NewGlobalRef(jvm_env, o_callback);
+  if (cbi->object == NULL) {
+    ERROR("java plugin: cjni_callback_info_create: NewGlobalRef failed.");
+    sfree(cbi->name);
+    sfree(cbi);
     return (NULL);
   }
 
-  cbi->class  = (*jvm_env)->GetObjectClass (jvm_env, cbi->object);
-  if (cbi->class == NULL)
-  {
-    ERROR ("java plugin: cjni_callback_info_create: GetObjectClass failed.");
-    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
-    sfree (cbi->name);
-    sfree (cbi);
+  cbi->class = (*jvm_env)->GetObjectClass(jvm_env, cbi->object);
+  if (cbi->class == NULL) {
+    ERROR("java plugin: cjni_callback_info_create: GetObjectClass failed.");
+    (*jvm_env)->DeleteGlobalRef(jvm_env, cbi->object);
+    sfree(cbi->name);
+    sfree(cbi);
     return (NULL);
   }
 
-  cbi->method = (*jvm_env)->GetMethodID (jvm_env, cbi->class,
-      method_name, method_signature);
-  if (cbi->method == NULL)
-  {
-    ERROR ("java plugin: cjni_callback_info_create: "
-        "Cannot find the `%s' method with signature `%s'.",
-        method_name, method_signature);
-    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
-    sfree (cbi->name);
-    sfree (cbi);
+  cbi->method = (*jvm_env)->GetMethodID(jvm_env, cbi->class, method_name,
+                                        method_signature);
+  if (cbi->method == NULL) {
+    ERROR("java plugin: cjni_callback_info_create: "
+          "Cannot find the `%s' method with signature `%s'.",
+          method_name, method_signature);
+    (*jvm_env)->DeleteGlobalRef(jvm_env, cbi->object);
+    sfree(cbi->name);
+    sfree(cbi);
     return (NULL);
   }
 
   return (cbi);
 } /* }}} cjni_callback_info_t cjni_callback_info_create */
 
 /* Allocate a `cjni_callback_info_t' via `cjni_callback_info_create' and add it
  * to the global `java_callbacks' variable. This is used for `config', `init',
  * and `shutdown' callbacks. */
-static int cjni_callback_register (JNIEnv *jvm_env, /* {{{ */
-    jobject o_name, jobject o_callback, int type)
-{
+static int cjni_callback_register(JNIEnv *jvm_env, /* {{{ */
+                                  jobject o_name, jobject o_callback,
+                                  int type) {
   cjni_callback_info_t *cbi;
   cjni_callback_info_t *tmp;
 #if COLLECT_DEBUG
   const char *type_str;
 #endif
 
-  cbi = cjni_callback_info_create (jvm_env, o_name, o_callback, type);
+  cbi = cjni_callback_info_create(jvm_env, o_name, o_callback, type);
   if (cbi == NULL)
     return (-1);
 
 #if COLLECT_DEBUG
-  switch (type)
-  {
-    case CB_TYPE_CONFIG:
-      type_str = "config";
-      break;
-
-    case CB_TYPE_INIT:
-      type_str = "init";
-      break;
-
-    case CB_TYPE_SHUTDOWN:
-      type_str = "shutdown";
-      break;
-
-    case CB_TYPE_MATCH:
-      type_str = "match";
-      break;
-
-    case CB_TYPE_TARGET:
-      type_str = "target";
-      break;
+  switch (type) {
+  case CB_TYPE_CONFIG:
+    type_str = "config";
+    break;
+
+  case CB_TYPE_INIT:
+    type_str = "init";
+    break;
+
+  case CB_TYPE_SHUTDOWN:
+    type_str = "shutdown";
+    break;
 
-    default:
-      type_str = "<unknown>";
+  case CB_TYPE_MATCH:
+    type_str = "match";
+    break;
+
+  case CB_TYPE_TARGET:
+    type_str = "target";
+    break;
+
+  default:
+    type_str = "<unknown>";
   }
-  DEBUG ("java plugin: Registering new %s callback: %s",
-      type_str, cbi->name);
+  DEBUG("java plugin: Registering new %s callback: %s", type_str, cbi->name);
 #endif
 
-  pthread_mutex_lock (&java_callbacks_lock);
+  pthread_mutex_lock(&java_callbacks_lock);
 
-  tmp = realloc (java_callbacks,
-      (java_callbacks_num + 1) * sizeof (*java_callbacks));
-  if (tmp == NULL)
-  {
-    pthread_mutex_unlock (&java_callbacks_lock);
-    ERROR ("java plugin: cjni_callback_register: realloc failed.");
+  tmp = realloc(java_callbacks,
+                (java_callbacks_num + 1) * sizeof(*java_callbacks));
+  if (tmp == NULL) {
+    pthread_mutex_unlock(&java_callbacks_lock);
+    ERROR("java plugin: cjni_callback_register: realloc failed.");
 
-    (*jvm_env)->DeleteGlobalRef (jvm_env, cbi->object);
-    free (cbi);
+    (*jvm_env)->DeleteGlobalRef(jvm_env, cbi->object);
+    free(cbi);
 
     return (-1);
   }
   java_callbacks = tmp;
   java_callbacks[java_callbacks_num] = *cbi;
   java_callbacks_num++;
 
-  pthread_mutex_unlock (&java_callbacks_lock);
+  pthread_mutex_unlock(&java_callbacks_lock);
 
-  free (cbi);
+  free(cbi);
   return (0);
 } /* }}} int cjni_callback_register */
 
 /* Callback for `pthread_key_create'. It frees the data contained in
  * `jvm_env_key' and prints a warning if the reference counter is not zero. */
-static void cjni_jvm_env_destroy (void *args) /* {{{ */
+static void cjni_jvm_env_destroy(void *args) /* {{{ */
 {
   cjni_jvm_env_t *cjni_env;
 
   if (args == NULL)
     return;
 
-  cjni_env = (cjni_jvm_env_t *) args;
+  cjni_env = (cjni_jvm_env_t *)args;
 
-  if (cjni_env->reference_counter > 0)
-  {
-    ERROR ("java plugin: cjni_jvm_env_destroy: "
-        "cjni_env->reference_counter = %i;", cjni_env->reference_counter);
+  if (cjni_env->reference_counter > 0) {
+    ERROR("java plugin: cjni_jvm_env_destroy: "
+          "cjni_env->reference_counter = %i;",
+          cjni_env->reference_counter);
   }
 
-  if (cjni_env->jvm_env != NULL)
-  {
-    ERROR ("java plugin: cjni_jvm_env_destroy: cjni_env->jvm_env = %p;",
-        (void *) cjni_env->jvm_env);
+  if (cjni_env->jvm_env != NULL) {
+    ERROR("java plugin: cjni_jvm_env_destroy: cjni_env->jvm_env = %p;",
+          (void *)cjni_env->jvm_env);
   }
 
   /* The pointer is allocated in `cjni_thread_attach' */
-  free (cjni_env);
+  free(cjni_env);
 } /* }}} void cjni_jvm_env_destroy */
 
 /* Register ``native'' functions with the JVM. Native functions are C-functions
  * that can be called by Java code. */
-static int cjni_init_native (JNIEnv *jvm_env) /* {{{ */
+static int cjni_init_native(JNIEnv *jvm_env) /* {{{ */
 {
   jclass api_class_ptr;
   int status;
 
-  api_class_ptr = (*jvm_env)->FindClass (jvm_env, "org/collectd/api/Collectd");
-  if (api_class_ptr == NULL)
-  {
-    ERROR ("cjni_init_native: Cannot find the API class \"org.collectd.api"
-        ".Collectd\". Please set the correct class path "
-        "using 'JVMArg \"-Djava.class.path=...\"'.");
+  api_class_ptr = (*jvm_env)->FindClass(jvm_env, "org/collectd/api/Collectd");
+  if (api_class_ptr == NULL) {
+    ERROR("cjni_init_native: Cannot find the API class \"org.collectd.api"
+          ".Collectd\". Please set the correct class path "
+          "using 'JVMArg \"-Djava.class.path=...\"'.");
     return (-1);
   }
 
-  status = (*jvm_env)->RegisterNatives (jvm_env, api_class_ptr,
-      jni_api_functions, (jint) jni_api_functions_num);
-  if (status != 0)
-  {
-    ERROR ("cjni_init_native: RegisterNatives failed with status %i.", status);
+  status = (*jvm_env)->RegisterNatives(
+      jvm_env, api_class_ptr, jni_api_functions, (jint)jni_api_functions_num);
+  if (status != 0) {
+    ERROR("cjni_init_native: RegisterNatives failed with status %i.", status);
     return (-1);
   }
 
   return (0);
 } /* }}} int cjni_init_native */
 
 /* Create the JVM. This is called when the first thread tries to access the JVM
  * via cjni_thread_attach. */
-static int cjni_create_jvm (void) /* {{{ */
+static int cjni_create_jvm(void) /* {{{ */
 {
   JNIEnv *jvm_env;
-  JavaVMInitArgs vm_args = { 0 };
+  JavaVMInitArgs vm_args = {0};
   JavaVMOption vm_options[jvm_argc];
 
   int status;
 
   if (jvm != NULL)
     return (0);
 
-  status = pthread_key_create (&jvm_env_key, cjni_jvm_env_destroy);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_create_jvm: pthread_key_create failed "
-        "with status %i.", status);
+  status = pthread_key_create(&jvm_env_key, cjni_jvm_env_destroy);
+  if (status != 0) {
+    ERROR("java plugin: cjni_create_jvm: pthread_key_create failed "
+          "with status %i.",
+          status);
     return (-1);
   }
 
   jvm_env = NULL;
 
   vm_args.version = JNI_VERSION_1_2;
   vm_args.options = vm_options;
-  vm_args.nOptions = (jint) jvm_argc;
+  vm_args.nOptions = (jint)jvm_argc;
 
-  for (size_t i = 0; i < jvm_argc; i++)
-  {
-    DEBUG ("java plugin: cjni_create_jvm: jvm_argv[%zu] = %s",
-        i, jvm_argv[i]);
+  for (size_t i = 0; i < jvm_argc; i++) {
+    DEBUG("java plugin: cjni_create_jvm: jvm_argv[%zu] = %s", i, jvm_argv[i]);
     vm_args.options[i].optionString = jvm_argv[i];
   }
 
-  status = JNI_CreateJavaVM (&jvm, (void *) &jvm_env, (void *) &vm_args);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_create_jvm: "
-        "JNI_CreateJavaVM failed with status %i.",
-	status);
+  status = JNI_CreateJavaVM(&jvm, (void *)&jvm_env, (void *)&vm_args);
+  if (status != 0) {
+    ERROR("java plugin: cjni_create_jvm: "
+          "JNI_CreateJavaVM failed with status %i.",
+          status);
     return (-1);
   }
-  assert (jvm != NULL);
-  assert (jvm_env != NULL);
+  assert(jvm != NULL);
+  assert(jvm_env != NULL);
 
   /* Call RegisterNatives */
-  status = cjni_init_native (jvm_env);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_create_jvm: cjni_init_native failed.");
+  status = cjni_init_native(jvm_env);
+  if (status != 0) {
+    ERROR("java plugin: cjni_create_jvm: cjni_init_native failed.");
     return (-1);
   }
 
-  DEBUG ("java plugin: The JVM has been created.");
+  DEBUG("java plugin: The JVM has been created.");
   return (0);
 } /* }}} int cjni_create_jvm */
 
 /* Increase the reference counter to the JVM for this thread. If it was zero,
  * attach the JVM first. */
-static JNIEnv *cjni_thread_attach (void) /* {{{ */
+static JNIEnv *cjni_thread_attach(void) /* {{{ */
 {
   cjni_jvm_env_t *cjni_env;
   JNIEnv *jvm_env;
 
   /* If we're the first thread to access the JVM, we'll have to create it
    * first.. */
-  if (jvm == NULL)
-  {
+  if (jvm == NULL) {
     int status;
 
-    status = cjni_create_jvm ();
-    if (status != 0)
-    {
-      ERROR ("java plugin: cjni_thread_attach: cjni_create_jvm failed.");
+    status = cjni_create_jvm();
+    if (status != 0) {
+      ERROR("java plugin: cjni_thread_attach: cjni_create_jvm failed.");
       return (NULL);
     }
   }
-  assert (jvm != NULL);
+  assert(jvm != NULL);
 
-  cjni_env = pthread_getspecific (jvm_env_key);
-  if (cjni_env == NULL)
-  {
+  cjni_env = pthread_getspecific(jvm_env_key);
+  if (cjni_env == NULL) {
     /* This pointer is free'd in `cjni_jvm_env_destroy'. */
-    cjni_env = calloc (1, sizeof (*cjni_env));
-    if (cjni_env == NULL)
-    {
-      ERROR ("java plugin: cjni_thread_attach: calloc failed.");
+    cjni_env = calloc(1, sizeof(*cjni_env));
+    if (cjni_env == NULL) {
+      ERROR("java plugin: cjni_thread_attach: calloc failed.");
       return (NULL);
     }
     cjni_env->reference_counter = 0;
     cjni_env->jvm_env = NULL;
 
-    pthread_setspecific (jvm_env_key, cjni_env);
+    pthread_setspecific(jvm_env_key, cjni_env);
   }
 
-  if (cjni_env->reference_counter > 0)
-  {
+  if (cjni_env->reference_counter > 0) {
     cjni_env->reference_counter++;
     jvm_env = cjni_env->jvm_env;
-  }
-  else
-  {
+  } else {
     int status;
-    JavaVMAttachArgs args = { 0 };
+    JavaVMAttachArgs args = {0};
 
-    assert (cjni_env->jvm_env == NULL);
+    assert(cjni_env->jvm_env == NULL);
 
     args.version = JNI_VERSION_1_2;
 
-    status = (*jvm)->AttachCurrentThread (jvm, (void *) &jvm_env, (void *) &args);
-    if (status != 0)
-    {
-      ERROR ("java plugin: cjni_thread_attach: AttachCurrentThread failed "
-          "with status %i.", status);
+    status = (*jvm)->AttachCurrentThread(jvm, (void *)&jvm_env, (void *)&args);
+    if (status != 0) {
+      ERROR("java plugin: cjni_thread_attach: AttachCurrentThread failed "
+            "with status %i.",
+            status);
       return (NULL);
     }
 
     cjni_env->reference_counter = 1;
     cjni_env->jvm_env = jvm_env;
   }
 
-  DEBUG ("java plugin: cjni_thread_attach: cjni_env->reference_counter = %i",
-      cjni_env->reference_counter);
-  assert (jvm_env != NULL);
+  DEBUG("java plugin: cjni_thread_attach: cjni_env->reference_counter = %i",
+        cjni_env->reference_counter);
+  assert(jvm_env != NULL);
   return (jvm_env);
 } /* }}} JNIEnv *cjni_thread_attach */
 
 /* Decrease the reference counter of this thread. If it reaches zero, detach
  * from the JVM. */
-static int cjni_thread_detach (void) /* {{{ */
+static int cjni_thread_detach(void) /* {{{ */
 {
   cjni_jvm_env_t *cjni_env;
   int status;
 
-  cjni_env = pthread_getspecific (jvm_env_key);
-  if (cjni_env == NULL)
-  {
-    ERROR ("java plugin: cjni_thread_detach: pthread_getspecific failed.");
+  cjni_env = pthread_getspecific(jvm_env_key);
+  if (cjni_env == NULL) {
+    ERROR("java plugin: cjni_thread_detach: pthread_getspecific failed.");
     return (-1);
   }
 
-  assert (cjni_env->reference_counter > 0);
-  assert (cjni_env->jvm_env != NULL);
+  assert(cjni_env->reference_counter > 0);
+  assert(cjni_env->jvm_env != NULL);
 
   cjni_env->reference_counter--;
-  DEBUG ("java plugin: cjni_thread_detach: cjni_env->reference_counter = %i",
-      cjni_env->reference_counter);
+  DEBUG("java plugin: cjni_thread_detach: cjni_env->reference_counter = %i",
+        cjni_env->reference_counter);
 
   if (cjni_env->reference_counter > 0)
     return (0);
 
-  status = (*jvm)->DetachCurrentThread (jvm);
-  if (status != 0)
-  {
-    ERROR ("java plugin: cjni_thread_detach: DetachCurrentThread failed "
-        "with status %i.", status);
+  status = (*jvm)->DetachCurrentThread(jvm);
+  if (status != 0) {
+    ERROR("java plugin: cjni_thread_detach: DetachCurrentThread failed "
+          "with status %i.",
+          status);
   }
 
   cjni_env->reference_counter = 0;
   cjni_env->jvm_env = NULL;
 
   return (0);
 } /* }}} int cjni_thread_detach */
 
-static int cjni_config_add_jvm_arg (oconfig_item_t *ci) /* {{{ */
+static int cjni_config_add_jvm_arg(oconfig_item_t *ci) /* {{{ */
 {
   char **tmp;
 
-  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
-  {
-    WARNING ("java plugin: `JVMArg' needs exactly one string argument.");
+  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
+    WARNING("java plugin: `JVMArg' needs exactly one string argument.");
     return (-1);
   }
 
-  if (jvm != NULL)
-  {
-    ERROR ("java plugin: All `JVMArg' options MUST appear before all "
-        "`LoadPlugin' options! The JVM is already started and I have to "
-        "ignore this argument: %s",
-        ci->values[0].value.string);
+  if (jvm != NULL) {
+    ERROR("java plugin: All `JVMArg' options MUST appear before all "
+          "`LoadPlugin' options! The JVM is already started and I have to "
+          "ignore this argument: %s",
+          ci->values[0].value.string);
     return (-1);
   }
 
-  tmp = realloc (jvm_argv, sizeof (char *) * (jvm_argc + 1));
-  if (tmp == NULL)
-  {
-    ERROR ("java plugin: realloc failed.");
+  tmp = realloc(jvm_argv, sizeof(char *) * (jvm_argc + 1));
+  if (tmp == NULL) {
+    ERROR("java plugin: realloc failed.");
     return (-1);
   }
   jvm_argv = tmp;
 
-  jvm_argv[jvm_argc] = strdup (ci->values[0].value.string);
-  if (jvm_argv[jvm_argc] == NULL)
-  {
-    ERROR ("java plugin: strdup failed.");
+  jvm_argv[jvm_argc] = strdup(ci->values[0].value.string);
+  if (jvm_argv[jvm_argc] == NULL) {
+    ERROR("java plugin: strdup failed.");
     return (-1);
   }
   jvm_argc++;
 
   return (0);
 } /* }}} int cjni_config_add_jvm_arg */
 
-static int cjni_config_load_plugin (oconfig_item_t *ci) /* {{{ */
+static int cjni_config_load_plugin(oconfig_item_t *ci) /* {{{ */
 {
   JNIEnv *jvm_env;
   java_plugin_class_t *class;
   jmethodID constructor_id;
   jobject tmp_object;
 
-  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
-  {
-    WARNING ("java plugin: `LoadPlugin' needs exactly one string argument.");
+  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
+    WARNING("java plugin: `LoadPlugin' needs exactly one string argument.");
     return (-1);
   }
 
-  jvm_env = cjni_thread_attach ();
+  jvm_env = cjni_thread_attach();
   if (jvm_env == NULL)
     return (-1);
 
-  class = realloc (java_classes_list,
-      (java_classes_list_len + 1) * sizeof (*java_classes_list));
-  if (class == NULL)
-  {
-    ERROR ("java plugin: realloc failed.");
-    cjni_thread_detach ();
+  class = realloc(java_classes_list,
+                  (java_classes_list_len + 1) * sizeof(*java_classes_list));
+  if (class == NULL) {
+    ERROR("java plugin: realloc failed.");
+    cjni_thread_detach();
     return (-1);
   }
   java_classes_list = class;
   class = java_classes_list + java_classes_list_len;
 
-  memset (class, 0, sizeof (*class));
-  class->name = strdup (ci->values[0].value.string);
-  if (class->name == NULL)
-  {
-    ERROR ("java plugin: strdup failed.");
-    cjni_thread_detach ();
+  memset(class, 0, sizeof(*class));
+  class->name = strdup(ci->values[0].value.string);
+  if (class->name == NULL) {
+    ERROR("java plugin: strdup failed.");
+    cjni_thread_detach();
     return (-1);
   }
   class->class = NULL;
   class->object = NULL;
 
   { /* Replace all dots ('.') with slashes ('/'). Dots are usually used
