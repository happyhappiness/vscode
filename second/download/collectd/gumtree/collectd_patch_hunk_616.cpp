 
     cf = le->value;
 
     /* do not switch plugin context; rather keep the context (interval)
      * information of the calling read plugin */
 
-    DEBUG ("plugin: plugin_write: Writing values via %s.", le->key);
+    DEBUG("plugin: plugin_write: Writing values via %s.", le->key);
     callback = cf->cf_callback;
-    status = (*callback) (ds, vl, &cf->cf_udata);
+    status = (*callback)(ds, vl, &cf->cf_udata);
   }
 
   return (status);
 } /* }}} int plugin_write */
 
-int plugin_flush (const char *plugin, cdtime_t timeout, const char *identifier)
-{
+int plugin_flush(const char *plugin, cdtime_t timeout, const char *identifier) {
   llentry_t *le;
 
   if (list_flush == NULL)
     return (0);
 
-  le = llist_head (list_flush);
-  while (le != NULL)
-  {
+  le = llist_head(list_flush);
+  while (le != NULL) {
     callback_func_t *cf;
     plugin_flush_cb callback;
     plugin_ctx_t old_ctx;
 
-    if ((plugin != NULL)
-        && (strcmp (plugin, le->key) != 0))
-    {
+    if ((plugin != NULL) && (strcmp(plugin, le->key) != 0)) {
       le = le->next;
       continue;
     }
 
     cf = le->value;
-    old_ctx = plugin_set_ctx (cf->cf_ctx);
+    old_ctx = plugin_set_ctx(cf->cf_ctx);
     callback = cf->cf_callback;
 
-    (*callback) (timeout, identifier, &cf->cf_udata);
+    (*callback)(timeout, identifier, &cf->cf_udata);
 
-    plugin_set_ctx (old_ctx);
+    plugin_set_ctx(old_ctx);
 
     le = le->next;
   }
   return (0);
 } /* int plugin_flush */
 
-int plugin_shutdown_all (void)
-{
-	llentry_t *le;
-	int ret = 0;  // Assume success.
+int plugin_shutdown_all(void) {
+  llentry_t *le;
+  int ret = 0; // Assume success.
+
+  destroy_all_callbacks(&list_init);
+
+  stop_read_threads();
+
+  pthread_mutex_lock(&read_lock);
+  llist_destroy(read_list);
+  read_list = NULL;
+  pthread_mutex_unlock(&read_lock);
 
-	destroy_all_callbacks (&list_init);
+  destroy_read_heap();
 
-	stop_read_threads ();
+  /* blocks until all write threads have shut down. */
+  stop_write_threads();
 
-	pthread_mutex_lock (&read_lock);
-	llist_destroy (read_list);
-	read_list = NULL;
-	pthread_mutex_unlock (&read_lock);
-
-	destroy_read_heap ();
-
-	/* blocks until all write threads have shut down. */
-	stop_write_threads ();
-
-	/* ask all plugins to write out the state they kept. */
-	plugin_flush (/* plugin = */ NULL,
-			/* timeout = */ 0,
-			/* identifier = */ NULL);
-
-	le = NULL;
-	if (list_shutdown != NULL)
-		le = llist_head (list_shutdown);
-
-	while (le != NULL)
-	{
-		callback_func_t *cf;
-		plugin_shutdown_cb callback;
-		plugin_ctx_t old_ctx;
-
-		cf = le->value;
-		old_ctx = plugin_set_ctx (cf->cf_ctx);
-		callback = cf->cf_callback;
-
-		/* Advance the pointer before calling the callback allows
-		 * shutdown functions to unregister themselves. If done the
-		 * other way around the memory `le' points to will be freed
-		 * after callback returns. */
-		le = le->next;
-
-		if ((*callback) () != 0)
-			ret = -1;
-
-		plugin_set_ctx (old_ctx);
-	}
-
-	/* Write plugins which use the `user_data' pointer usually need the
-	 * same data available to the flush callback. If this is the case, set
-	 * the free_function to NULL when registering the flush callback and to
-	 * the real free function when registering the write callback. This way
-	 * the data isn't freed twice. */
-	destroy_all_callbacks (&list_flush);
-	destroy_all_callbacks (&list_missing);
-	destroy_all_callbacks (&list_write);
-
-	destroy_all_callbacks (&list_notification);
-	destroy_all_callbacks (&list_shutdown);
-	destroy_all_callbacks (&list_log);
-
-	plugin_free_loaded ();
-	plugin_free_data_sets ();
-	return (ret);
+  /* ask all plugins to write out the state they kept. */
+  plugin_flush(/* plugin = */ NULL,
+               /* timeout = */ 0,
+               /* identifier = */ NULL);
+
+  le = NULL;
+  if (list_shutdown != NULL)
+    le = llist_head(list_shutdown);
+
+  while (le != NULL) {
+    callback_func_t *cf;
+    plugin_shutdown_cb callback;
+    plugin_ctx_t old_ctx;
+
+    cf = le->value;
+    old_ctx = plugin_set_ctx(cf->cf_ctx);
+    callback = cf->cf_callback;
+
+    /* Advance the pointer before calling the callback allows
+     * shutdown functions to unregister themselves. If done the
+     * other way around the memory `le' points to will be freed
+     * after callback returns. */
+    le = le->next;
+
+    if ((*callback)() != 0)
+      ret = -1;
+
+    plugin_set_ctx(old_ctx);
+  }
+
+  /* Write plugins which use the `user_data' pointer usually need the
+   * same data available to the flush callback. If this is the case, set
+   * the free_function to NULL when registering the flush callback and to
+   * the real free function when registering the write callback. This way
+   * the data isn't freed twice. */
+  destroy_all_callbacks(&list_flush);
+  destroy_all_callbacks(&list_missing);
+  destroy_all_callbacks(&list_write);
+
+  destroy_all_callbacks(&list_notification);
+  destroy_all_callbacks(&list_shutdown);
+  destroy_all_callbacks(&list_log);
+
+  plugin_free_loaded();
+  plugin_free_data_sets();
+  return (ret);
 } /* void plugin_shutdown_all */
 
-int plugin_dispatch_missing (const value_list_t *vl) /* {{{ */
+int plugin_dispatch_missing(const value_list_t *vl) /* {{{ */
 {
   llentry_t *le;
 
   if (list_missing == NULL)
     return (0);
 
-  le = llist_head (list_missing);
-  while (le != NULL)
-  {
+  le = llist_head(list_missing);
+  while (le != NULL) {
     callback_func_t *cf;
     plugin_missing_cb callback;
     plugin_ctx_t old_ctx;
     int status;
 
     cf = le->value;
-    old_ctx = plugin_set_ctx (cf->cf_ctx);
+    old_ctx = plugin_set_ctx(cf->cf_ctx);
     callback = cf->cf_callback;
 
-    status = (*callback) (vl, &cf->cf_udata);
-    plugin_set_ctx (old_ctx);
-    if (status != 0)
-    {
-      if (status < 0)
-      {
-        ERROR ("plugin_dispatch_missing: Callback function \"%s\" "
-            "failed with status %i.",
-            le->key, status);
+    status = (*callback)(vl, &cf->cf_udata);
+    plugin_set_ctx(old_ctx);
+    if (status != 0) {
+      if (status < 0) {
+        ERROR("plugin_dispatch_missing: Callback function \"%s\" "
+              "failed with status %i.",
+              le->key, status);
         return (status);
-      }
-      else
-      {
+      } else {
         return (0);
       }
     }
 
     le = le->next;
   }
   return (0);
 } /* int }}} plugin_dispatch_missing */
 
-static int plugin_dispatch_values_internal (value_list_t *vl)
-{
-	int status;
-	static c_complain_t no_write_complaint = C_COMPLAIN_INIT_STATIC;
+static int plugin_dispatch_values_internal(value_list_t *vl) {
+  int status;
+  static c_complain_t no_write_complaint = C_COMPLAIN_INIT_STATIC;
+
+  value_t *saved_values;
+  int saved_values_len;
+
+  data_set_t *ds;
+
+  int free_meta_data = 0;
+
+  assert(vl);
+  assert(vl->plugin);
+
+  if (vl->type[0] == 0 || vl->values == NULL || vl->values_len < 1) {
+    ERROR("plugin_dispatch_values: Invalid value list "
+          "from plugin %s.",
+          vl->plugin);
+    return (-1);
+  }
+
+  /* Free meta data only if the calling function didn't specify any. In
+   * this case matches and targets may add some and the calling function
+   * may not expect (and therefore free) that data. */
+  if (vl->meta == NULL)
+    free_meta_data = 1;
+
+  if (list_write == NULL)
+    c_complain_once(LOG_WARNING, &no_write_complaint,
+                    "plugin_dispatch_values: No write callback has been "
+                    "registered. Please load at least one output plugin, "
+                    "if you want the collected data to be stored.");
+
+  if (data_sets == NULL) {
+    ERROR("plugin_dispatch_values: No data sets registered. "
+          "Could the types database be read? Check "
+          "your `TypesDB' setting!");
+    return (-1);
+  }
 
-	value_t *saved_values;
-	int      saved_values_len;
+  if (c_avl_get(data_sets, vl->type, (void *)&ds) != 0) {
+    char ident[6 * DATA_MAX_NAME_LEN];
 
-	data_set_t *ds;
+    FORMAT_VL(ident, sizeof(ident), vl);
+    INFO("plugin_dispatch_values: Dataset not found: %s "
+         "(from \"%s\"), check your types.db!",
+         vl->type, ident);
+    return (-1);
+  }
 
-	int free_meta_data = 0;
-
-	assert(vl);
-	assert(vl->plugin);
-
-	if (vl->type[0] == 0 || vl->values == NULL || vl->values_len < 1)
-	{
-		ERROR ("plugin_dispatch_values: Invalid value list "
-				"from plugin %s.", vl->plugin);
-		return (-1);
-	}
-
-	/* Free meta data only if the calling function didn't specify any. In
-	 * this case matches and targets may add some and the calling function
-	 * may not expect (and therefore free) that data. */
-	if (vl->meta == NULL)
-		free_meta_data = 1;
-
-	if (list_write == NULL)
-		c_complain_once (LOG_WARNING, &no_write_complaint,
-				"plugin_dispatch_values: No write callback has been "
-				"registered. Please load at least one output plugin, "
-				"if you want the collected data to be stored.");
-
-	if (data_sets == NULL)
-	{
-		ERROR ("plugin_dispatch_values: No data sets registered. "
-				"Could the types database be read? Check "
-				"your `TypesDB' setting!");
-		return (-1);
-	}
-
-	if (c_avl_get (data_sets, vl->type, (void *) &ds) != 0)
-	{
-		char ident[6 * DATA_MAX_NAME_LEN];
-
-		FORMAT_VL (ident, sizeof (ident), vl);
-		INFO ("plugin_dispatch_values: Dataset not found: %s "
-				"(from \"%s\"), check your types.db!",
-				vl->type, ident);
-		return (-1);
-	}
-
-	/* Assured by plugin_value_list_clone(). The time is determined at
-	 * _enqueue_ time. */
-	assert (vl->time != 0);
-	assert (vl->interval != 0);
-
-	DEBUG ("plugin_dispatch_values: time = %.3f; interval = %.3f; "
-			"host = %s; "
-			"plugin = %s; plugin_instance = %s; "
-			"type = %s; type_instance = %s;",
-			CDTIME_T_TO_DOUBLE (vl->time),
-			CDTIME_T_TO_DOUBLE (vl->interval),
-			vl->host,
-			vl->plugin, vl->plugin_instance,
-			vl->type, vl->type_instance);
+  /* Assured by plugin_value_list_clone(). The time is determined at
+   * _enqueue_ time. */
+  assert(vl->time != 0);
+  assert(vl->interval != 0);
+
+  DEBUG("plugin_dispatch_values: time = %.3f; interval = %.3f; "
+        "host = %s; "
+        "plugin = %s; plugin_instance = %s; "
+        "type = %s; type_instance = %s;",
+        CDTIME_T_TO_DOUBLE(vl->time), CDTIME_T_TO_DOUBLE(vl->interval),
+        vl->host, vl->plugin, vl->plugin_instance, vl->type, vl->type_instance);
 
 #if COLLECT_DEBUG
-	assert (0 == strcmp (ds->type, vl->type));
+  assert(0 == strcmp(ds->type, vl->type));
 #else
-	if (0 != strcmp (ds->type, vl->type))
-		WARNING ("plugin_dispatch_values: (ds->type = %s) != (vl->type = %s)",
-				ds->type, vl->type);
+  if (0 != strcmp(ds->type, vl->type))
+    WARNING("plugin_dispatch_values: (ds->type = %s) != (vl->type = %s)",
+            ds->type, vl->type);
 #endif
 
 #if COLLECT_DEBUG
-	assert (ds->ds_num == vl->values_len);
+  assert(ds->ds_num == vl->values_len);
 #else
-	if (ds->ds_num != vl->values_len)
-	{
-		ERROR ("plugin_dispatch_values: ds->type = %s: "
-				"(ds->ds_num = %zu) != "
-				"(vl->values_len = %zu)",
-				ds->type, ds->ds_num, vl->values_len);
-		return (-1);
-	}
+  if (ds->ds_num != vl->values_len) {
+    ERROR("plugin_dispatch_values: ds->type = %s: "
+          "(ds->ds_num = %zu) != "
+          "(vl->values_len = %zu)",
+          ds->type, ds->ds_num, vl->values_len);
+    return (-1);
+  }
 #endif
 
-	escape_slashes (vl->host, sizeof (vl->host));
-	escape_slashes (vl->plugin, sizeof (vl->plugin));
-	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
-	escape_slashes (vl->type, sizeof (vl->type));
-	escape_slashes (vl->type_instance, sizeof (vl->type_instance));
-
-	/* Copy the values. This way, we can assure `targets' that they get
-	 * dynamically allocated values, which they can free and replace if
-	 * they like. */
-	if ((pre_cache_chain != NULL) || (post_cache_chain != NULL))
-	{
-		saved_values     = vl->values;
-		saved_values_len = vl->values_len;
-
-		vl->values = (value_t *) calloc (vl->values_len,
-				sizeof (*vl->values));
-		if (vl->values == NULL)
-		{
-			ERROR ("plugin_dispatch_values: calloc failed.");
-			vl->values = saved_values;
-			return (-1);
-		}
-		memcpy (vl->values, saved_values,
-				vl->values_len * sizeof (*vl->values));
-	}
-	else /* if ((pre == NULL) && (post == NULL)) */
-	{
-		saved_values     = NULL;
-		saved_values_len = 0;
-	}
-
-	if (pre_cache_chain != NULL)
-	{
-		status = fc_process_chain (ds, vl, pre_cache_chain);
-		if (status < 0)
-		{
-			WARNING ("plugin_dispatch_values: Running the "
-					"pre-cache chain failed with "
-					"status %i (%#x).",
-					status, status);
-		}
-		else if (status == FC_TARGET_STOP)
-		{
-			/* Restore the state of the value_list so that plugins
-			 * don't get confused.. */
-			if (saved_values != NULL)
-			{
-				sfree (vl->values);
-				vl->values     = saved_values;
-				vl->values_len = saved_values_len;
-			}
-			return (0);
-		}
-	}
-
-	/* Update the value cache */
-	uc_update (ds, vl);
-
-	if (post_cache_chain != NULL)
-	{
-		status = fc_process_chain (ds, vl, post_cache_chain);
-		if (status < 0)
-		{
-			WARNING ("plugin_dispatch_values: Running the "
-					"post-cache chain failed with "
-					"status %i (%#x).",
-					status, status);
-		}
-	}
-	else
-		fc_default_action (ds, vl);
-
-	/* Restore the state of the value_list so that plugins don't get
-	 * confused.. */
-	if (saved_values != NULL)
-	{
-		sfree (vl->values);
-		vl->values     = saved_values;
-		vl->values_len = saved_values_len;
-	}
-
-	if ((free_meta_data != 0) && (vl->meta != NULL))
-	{
-		meta_data_destroy (vl->meta);
-		vl->meta = NULL;
-	}
+  escape_slashes(vl->host, sizeof(vl->host));
+  escape_slashes(vl->plugin, sizeof(vl->plugin));
+  escape_slashes(vl->plugin_instance, sizeof(vl->plugin_instance));
+  escape_slashes(vl->type, sizeof(vl->type));
+  escape_slashes(vl->type_instance, sizeof(vl->type_instance));
+
+  /* Copy the values. This way, we can assure `targets' that they get
+   * dynamically allocated values, which they can free and replace if
+   * they like. */
+  if ((pre_cache_chain != NULL) || (post_cache_chain != NULL)) {
+    saved_values = vl->values;
+    saved_values_len = vl->values_len;
+
+    vl->values = (value_t *)calloc(vl->values_len, sizeof(*vl->values));
+    if (vl->values == NULL) {
+      ERROR("plugin_dispatch_values: calloc failed.");
+      vl->values = saved_values;
+      return (-1);
+    }
+    memcpy(vl->values, saved_values, vl->values_len * sizeof(*vl->values));
+  } else /* if ((pre == NULL) && (post == NULL)) */
+  {
+    saved_values = NULL;
+    saved_values_len = 0;
+  }
+
+  if (pre_cache_chain != NULL) {
+    status = fc_process_chain(ds, vl, pre_cache_chain);
+    if (status < 0) {
+      WARNING("plugin_dispatch_values: Running the "
+              "pre-cache chain failed with "
+              "status %i (%#x).",
+              status, status);
+    } else if (status == FC_TARGET_STOP) {
+      /* Restore the state of the value_list so that plugins
+       * don't get confused.. */
+      if (saved_values != NULL) {
+        sfree(vl->values);
+        vl->values = saved_values;
+        vl->values_len = saved_values_len;
+      }
+      return (0);
+    }
+  }
+
+  /* Update the value cache */
+  uc_update(ds, vl);
 
-	return (0);
+  if (post_cache_chain != NULL) {
+    status = fc_process_chain(ds, vl, post_cache_chain);
+    if (status < 0) {
+      WARNING("plugin_dispatch_values: Running the "
+              "post-cache chain failed with "
+              "status %i (%#x).",
+              status, status);
+    }
+  } else
+    fc_default_action(ds, vl);
+
+  /* Restore the state of the value_list so that plugins don't get
+   * confused.. */
+  if (saved_values != NULL) {
+    sfree(vl->values);
+    vl->values = saved_values;
+    vl->values_len = saved_values_len;
+  }
+
+  if ((free_meta_data != 0) && (vl->meta != NULL)) {
+    meta_data_destroy(vl->meta);
+    vl->meta = NULL;
+  }
+
+  return (0);
 } /* int plugin_dispatch_values_internal */
 
-static double get_drop_probability (void) /* {{{ */
+static double get_drop_probability(void) /* {{{ */
 {
-	long pos;
-	long size;
-	long wql;
-
-	pthread_mutex_lock (&write_lock);
-	wql = write_queue_length;
-	pthread_mutex_unlock (&write_lock);
-
-	if (wql < write_limit_low)
-		return (0.0);
-	if (wql >= write_limit_high)
-		return (1.0);
+  long pos;
+  long size;
+  long wql;
+
+  pthread_mutex_lock(&write_lock);
+  wql = write_queue_length;
+  pthread_mutex_unlock(&write_lock);
 
-	pos = 1 + wql - write_limit_low;
-	size = 1 + write_limit_high - write_limit_low;
+  if (wql < write_limit_low)
+    return (0.0);
+  if (wql >= write_limit_high)
+    return (1.0);
 
-	return (((double) pos) / ((double) size));
+  pos = 1 + wql - write_limit_low;
+  size = 1 + write_limit_high - write_limit_low;
+
+  return (((double)pos) / ((double)size));
 } /* }}} double get_drop_probability */
 
-static _Bool check_drop_value (void) /* {{{ */
+static _Bool check_drop_value(void) /* {{{ */
 {
-	static cdtime_t last_message_time = 0;
-	static pthread_mutex_t last_message_lock = PTHREAD_MUTEX_INITIALIZER;
+  static cdtime_t last_message_time = 0;
+  static pthread_mutex_t last_message_lock = PTHREAD_MUTEX_INITIALIZER;
+
+  double p;
+  double q;
+  int status;
+
+  if (write_limit_high == 0)
+    return (0);
+
+  p = get_drop_probability();
+  if (p == 0.0)
+    return (0);
+
+  status = pthread_mutex_trylock(&last_message_lock);
+  if (status == 0) {
+    cdtime_t now;
+
+    now = cdtime();
+    if ((now - last_message_time) > TIME_T_TO_CDTIME_T(1)) {
+      last_message_time = now;
+      ERROR("plugin_dispatch_values: Low water mark "
+            "reached. Dropping %.0f%% of metrics.",
+            100.0 * p);
+    }
+    pthread_mutex_unlock(&last_message_lock);
+  }
 
-	double p;
-	double q;
-	int status;
-
-	if (write_limit_high == 0)
-		return (0);
-
-	p = get_drop_probability ();
-	if (p == 0.0)
-		return (0);
-
-	status = pthread_mutex_trylock (&last_message_lock);
-	if (status == 0)
-	{
-		cdtime_t now;
-
-		now = cdtime ();
-		if ((now - last_message_time) > TIME_T_TO_CDTIME_T (1))
-		{
-			last_message_time = now;
-			ERROR ("plugin_dispatch_values: Low water mark "
-					"reached. Dropping %.0f%% of metrics.",
-					100.0 * p);
-		}
-		pthread_mutex_unlock (&last_message_lock);
-	}
-
-	if (p == 1.0)
-		return (1);
-
-	q = cdrand_d ();
-	if (q > p)
-		return (1);
-	else
-		return (0);
+  if (p == 1.0)
+    return (1);
+
+  q = cdrand_d();
+  if (q > p)
+    return (1);
+  else
+    return (0);
 } /* }}} _Bool check_drop_value */
 
-int plugin_dispatch_values (value_list_t const *vl)
-{
-	int status;
-	static pthread_mutex_t statistics_lock = PTHREAD_MUTEX_INITIALIZER;
+int plugin_dispatch_values(value_list_t const *vl) {
+  int status;
+  static pthread_mutex_t statistics_lock = PTHREAD_MUTEX_INITIALIZER;
+
+  if (check_drop_value()) {
+    if (record_statistics) {
+      pthread_mutex_lock(&statistics_lock);
+      stats_values_dropped++;
+      pthread_mutex_unlock(&statistics_lock);
+    }
+    return (0);
+  }
 
-	if (check_drop_value ()) {
-		if(record_statistics) {
-			pthread_mutex_lock(&statistics_lock);
-			stats_values_dropped++;
-			pthread_mutex_unlock(&statistics_lock);
-		}
-		return (0);
-	}
-
-	status = plugin_write_enqueue (vl);
-	if (status != 0)
-	{
-		char errbuf[1024];
-		ERROR ("plugin_dispatch_values: plugin_write_enqueue failed "
-				"with status %i (%s).", status,
-				sstrerror (status, errbuf, sizeof (errbuf)));
-		return (status);
-	}
+  status = plugin_write_enqueue(vl);
+  if (status != 0) {
+    char errbuf[1024];
+    ERROR("plugin_dispatch_values: plugin_write_enqueue failed "
+          "with status %i (%s).",
+          status, sstrerror(status, errbuf, sizeof(errbuf)));
+    return (status);
+  }
 
-	return (0);
+  return (0);
 }
 
-__attribute__((sentinel))
-int plugin_dispatch_multivalue (value_list_t const *template, /* {{{ */
-		_Bool store_percentage, int store_type, ...)
-{
-	value_list_t *vl;
-	int failed = 0;
-	gauge_t sum = 0.0;
-	va_list ap;
-
-	assert (template->values_len == 1);
-
-	/* Calculate sum for Gauge to calculate percent if needed */
-	if (DS_TYPE_GAUGE == store_type)	{
-		va_start (ap, store_type);
-		while (42)
-		{
-			char const *name;
-			gauge_t value;
-
-			name = va_arg (ap, char const *);
-			if (name == NULL)
-				break;
-
-			value = va_arg (ap, gauge_t);
-			if (!isnan (value))
-				sum += value;
-		}
-		va_end (ap);
-	}
-
-
-	vl = plugin_value_list_clone (template);
-	/* plugin_value_list_clone makes sure vl->time is set to non-zero. */
-	if (store_percentage)
-		sstrncpy (vl->type, "percent", sizeof (vl->type));
-
-	va_start (ap, store_type);
-	while (42)
-	{
-		char const *name;
-		int status;
-
-		/* Set the type instance. */
-		name = va_arg (ap, char const *);
-		if (name == NULL)
-			break;
-		sstrncpy (vl->type_instance, name, sizeof (vl->type_instance));
-
-		/* Set the value. */
-		switch (store_type)
-		{
-		case DS_TYPE_GAUGE:
-			vl->values[0].gauge = va_arg (ap, gauge_t);
-			if (store_percentage)
-				vl->values[0].gauge *= sum ? (100.0 / sum) : NAN;
-			break;
-		case DS_TYPE_ABSOLUTE:
-			vl->values[0].absolute = va_arg (ap, absolute_t);
-			break;
-		case DS_TYPE_COUNTER:
-			vl->values[0].counter  = va_arg (ap, counter_t);
-			break;
-		case DS_TYPE_DERIVE:
-			vl->values[0].derive   = va_arg (ap, derive_t);
-			break;
-		default:
-			ERROR ("plugin_dispatch_multivalue: given store_type is incorrect.");
-			failed++;
-		}
-
-
-		status = plugin_write_enqueue (vl);
-		if (status != 0)
-			failed++;
-	}
-	va_end (ap);
+__attribute__((sentinel)) int
+plugin_dispatch_multivalue(value_list_t const *template, /* {{{ */
+                           _Bool store_percentage, int store_type, ...) {
+  value_list_t *vl;
+  int failed = 0;
+  gauge_t sum = 0.0;
+  va_list ap;
+
+  assert(template->values_len == 1);
+
+  /* Calculate sum for Gauge to calculate percent if needed */
+  if (DS_TYPE_GAUGE == store_type) {
+    va_start(ap, store_type);
+    while (42) {
+      char const *name;
+      gauge_t value;
+
+      name = va_arg(ap, char const *);
+      if (name == NULL)
+        break;
+
+      value = va_arg(ap, gauge_t);
+      if (!isnan(value))
+        sum += value;
+    }
+    va_end(ap);
+  }
+
+  vl = plugin_value_list_clone(template);
+  /* plugin_value_list_clone makes sure vl->time is set to non-zero. */
+  if (store_percentage)
+    sstrncpy(vl->type, "percent", sizeof(vl->type));
+
+  va_start(ap, store_type);
+  while (42) {
+    char const *name;
+    int status;
+
+    /* Set the type instance. */
+    name = va_arg(ap, char const *);
+    if (name == NULL)
+      break;
+    sstrncpy(vl->type_instance, name, sizeof(vl->type_instance));
+
+    /* Set the value. */
+    switch (store_type) {
+    case DS_TYPE_GAUGE:
+      vl->values[0].gauge = va_arg(ap, gauge_t);
+      if (store_percentage)
+        vl->values[0].gauge *= sum ? (100.0 / sum) : NAN;
+      break;
+    case DS_TYPE_ABSOLUTE:
+      vl->values[0].absolute = va_arg(ap, absolute_t);
+      break;
+    case DS_TYPE_COUNTER:
+      vl->values[0].counter = va_arg(ap, counter_t);
+      break;
+    case DS_TYPE_DERIVE:
+      vl->values[0].derive = va_arg(ap, derive_t);
+      break;
+    default:
+      ERROR("plugin_dispatch_multivalue: given store_type is incorrect.");
+      failed++;
+    }
+
+    status = plugin_write_enqueue(vl);
+    if (status != 0)
+      failed++;
+  }
+  va_end(ap);
 
-	plugin_value_list_free (vl);
-	return (failed);
+  plugin_value_list_free(vl);
+  return (failed);
 } /* }}} int plugin_dispatch_multivalue */
 
-int plugin_dispatch_notification (const notification_t *notif)
-{
-	llentry_t *le;
-	/* Possible TODO: Add flap detection here */
+int plugin_dispatch_notification(const notification_t *notif) {
+  llentry_t *le;
+  /* Possible TODO: Add flap detection here */
 
-	DEBUG ("plugin_dispatch_notification: severity = %i; message = %s; "
-			"time = %.3f; host = %s;",
-			notif->severity, notif->message,
-			CDTIME_T_TO_DOUBLE (notif->time), notif->host);
-
-	/* Nobody cares for notifications */
-	if (list_notification == NULL)
-		return (-1);
-
-	le = llist_head (list_notification);
-	while (le != NULL)
-	{
-		callback_func_t *cf;
-		plugin_notification_cb callback;
-		int status;
-
-		/* do not switch plugin context; rather keep the context
-		 * (interval) information of the calling plugin */
-
-		cf = le->value;
-		callback = cf->cf_callback;
-		status = (*callback) (notif, &cf->cf_udata);
-		if (status != 0)
-		{
-			WARNING ("plugin_dispatch_notification: Notification "
-					"callback %s returned %i.",
-					le->key, status);
-		}
+  DEBUG("plugin_dispatch_notification: severity = %i; message = %s; "
+        "time = %.3f; host = %s;",
+        notif->severity, notif->message, CDTIME_T_TO_DOUBLE(notif->time),
+        notif->host);
 
-		le = le->next;
-	}
+  /* Nobody cares for notifications */
+  if (list_notification == NULL)
+    return (-1);
 
-	return (0);
+  le = llist_head(list_notification);
+  while (le != NULL) {
+    callback_func_t *cf;
+    plugin_notification_cb callback;
+    int status;
+
+    /* do not switch plugin context; rather keep the context
+     * (interval) information of the calling plugin */
+
+    cf = le->value;
+    callback = cf->cf_callback;
+    status = (*callback)(notif, &cf->cf_udata);
+    if (status != 0) {
+      WARNING("plugin_dispatch_notification: Notification "
+              "callback %s returned %i.",
+              le->key, status);
+    }
+
+    le = le->next;
+  }
+
+  return (0);
 } /* int plugin_dispatch_notification */
 
-void plugin_log (int level, const char *format, ...)
-{
-	char msg[1024];
-	va_list ap;
-	llentry_t *le;
+void plugin_log(int level, const char *format, ...) {
+  char msg[1024];
+  va_list ap;
+  llentry_t *le;
 
 #if !COLLECT_DEBUG
-	if (level >= LOG_DEBUG)
-		return;
+  if (level >= LOG_DEBUG)
+    return;
 #endif
 
-	va_start (ap, format);
-	vsnprintf (msg, sizeof (msg), format, ap);
-	msg[sizeof (msg) - 1] = '\0';
-	va_end (ap);
-
-	if (list_log == NULL)
-	{
-		fprintf (stderr, "%s\n", msg);
-		return;
-	}
-
-	le = llist_head (list_log);
-	while (le != NULL)
-	{
-		callback_func_t *cf;
-		plugin_log_cb callback;
-
-		cf = le->value;
-		callback = cf->cf_callback;
+  va_start(ap, format);
+  vsnprintf(msg, sizeof(msg), format, ap);
+  msg[sizeof(msg) - 1] = '\0';
+  va_end(ap);
+
+  if (list_log == NULL) {
+    fprintf(stderr, "%s\n", msg);
+    return;
+  }
+
+  le = llist_head(list_log);
+  while (le != NULL) {
+    callback_func_t *cf;
+    plugin_log_cb callback;
+
+    cf = le->value;
+    callback = cf->cf_callback;
 
-		/* do not switch plugin context; rather keep the context
-		 * (interval) information of the calling plugin */
+    /* do not switch plugin context; rather keep the context
+     * (interval) information of the calling plugin */
 
-		(*callback) (level, msg, &cf->cf_udata);
+    (*callback)(level, msg, &cf->cf_udata);
 
-		le = le->next;
-	}
+    le = le->next;
+  }
 } /* void plugin_log */
 
-int parse_log_severity (const char *severity)
-{
-	int log_level = -1;
+int parse_log_severity(const char *severity) {
+  int log_level = -1;
 
-	if ((0 == strcasecmp (severity, "emerg"))
-			|| (0 == strcasecmp (severity, "alert"))
-			|| (0 == strcasecmp (severity, "crit"))
-			|| (0 == strcasecmp (severity, "err")))
-		log_level = LOG_ERR;
-	else if (0 == strcasecmp (severity, "warning"))
-		log_level = LOG_WARNING;
-	else if (0 == strcasecmp (severity, "notice"))
-		log_level = LOG_NOTICE;
-	else if (0 == strcasecmp (severity, "info"))
-		log_level = LOG_INFO;
+  if ((0 == strcasecmp(severity, "emerg")) ||
+      (0 == strcasecmp(severity, "alert")) ||
+      (0 == strcasecmp(severity, "crit")) || (0 == strcasecmp(severity, "err")))
+    log_level = LOG_ERR;
+  else if (0 == strcasecmp(severity, "warning"))
+    log_level = LOG_WARNING;
+  else if (0 == strcasecmp(severity, "notice"))
+    log_level = LOG_NOTICE;
+  else if (0 == strcasecmp(severity, "info"))
+    log_level = LOG_INFO;
 #if COLLECT_DEBUG
-	else if (0 == strcasecmp (severity, "debug"))
-		log_level = LOG_DEBUG;
+  else if (0 == strcasecmp(severity, "debug"))
+    log_level = LOG_DEBUG;
 #endif /* COLLECT_DEBUG */
 
-	return (log_level);
+  return (log_level);
 } /* int parse_log_severity */
 
-int parse_notif_severity (const char *severity)
-{
-	int notif_severity = -1;
+int parse_notif_severity(const char *severity) {
+  int notif_severity = -1;
 
-	if (strcasecmp (severity, "FAILURE") == 0)
-		notif_severity = NOTIF_FAILURE;
-	else if (strcmp (severity, "OKAY") == 0)
-		notif_severity = NOTIF_OKAY;
-	else if ((strcmp (severity, "WARNING") == 0)
-			|| (strcmp (severity, "WARN") == 0))
-		notif_severity = NOTIF_WARNING;
+  if (strcasecmp(severity, "FAILURE") == 0)
+    notif_severity = NOTIF_FAILURE;
+  else if (strcmp(severity, "OKAY") == 0)
+    notif_severity = NOTIF_OKAY;
+  else if ((strcmp(severity, "WARNING") == 0) ||
+           (strcmp(severity, "WARN") == 0))
+    notif_severity = NOTIF_WARNING;
 
-	return (notif_severity);
+  return (notif_severity);
 } /* int parse_notif_severity */
 
-const data_set_t *plugin_get_ds (const char *name)
-{
-	data_set_t *ds;
+const data_set_t *plugin_get_ds(const char *name) {
+  data_set_t *ds;
+
+  if (data_sets == NULL) {
+    ERROR("plugin_get_ds: No data sets are defined yet.");
+    return (NULL);
+  }
 
-	if (data_sets == NULL)
-	{
-		ERROR ("plugin_get_ds: No data sets are defined yet.");
-		return (NULL);
-	}
-
-	if (c_avl_get (data_sets, name, (void *) &ds) != 0)
-	{
-		DEBUG ("No such dataset registered: %s", name);
-		return (NULL);
-	}
+  if (c_avl_get(data_sets, name, (void *)&ds) != 0) {
+    DEBUG("No such dataset registered: %s", name);
+    return (NULL);
+  }
 
-	return (ds);
+  return (ds);
 } /* data_set_t *plugin_get_ds */
 
-static int plugin_notification_meta_add (notification_t *n,
-    const char *name,
-    enum notification_meta_type_e type,
-    const void *value)
-{
+static int plugin_notification_meta_add(notification_t *n, const char *name,
+                                        enum notification_meta_type_e type,
+                                        const void *value) {
   notification_meta_t *meta;
   notification_meta_t *tail;
 
-  if ((n == NULL) || (name == NULL) || (value == NULL))
-  {
-    ERROR ("plugin_notification_meta_add: A pointer is NULL!");
+  if ((n == NULL) || (name == NULL) || (value == NULL)) {
+    ERROR("plugin_notification_meta_add: A pointer is NULL!");
     return (-1);
   }
 
-  meta = calloc (1, sizeof (*meta));
-  if (meta == NULL)
-  {
-    ERROR ("plugin_notification_meta_add: calloc failed.");
+  meta = calloc(1, sizeof(*meta));
+  if (meta == NULL) {
+    ERROR("plugin_notification_meta_add: calloc failed.");
     return (-1);
   }
 
-  sstrncpy (meta->name, name, sizeof (meta->name));
+  sstrncpy(meta->name, name, sizeof(meta->name));
   meta->type = type;
 
-  switch (type)
-  {
-    case NM_TYPE_STRING:
-    {
-      meta->nm_value.nm_string = strdup ((const char *) value);
-      if (meta->nm_value.nm_string == NULL)
-      {
-        ERROR ("plugin_notification_meta_add: strdup failed.");
-        sfree (meta);
-        return (-1);
-      }
-      break;
-    }
-    case NM_TYPE_SIGNED_INT:
-    {
-      meta->nm_value.nm_signed_int = *((int64_t *) value);
-      break;
-    }
-    case NM_TYPE_UNSIGNED_INT:
-    {
-      meta->nm_value.nm_unsigned_int = *((uint64_t *) value);
-      break;
-    }
-    case NM_TYPE_DOUBLE:
-    {
-      meta->nm_value.nm_double = *((double *) value);
-      break;
-    }
-    case NM_TYPE_BOOLEAN:
-    {
-      meta->nm_value.nm_boolean = *((_Bool *) value);
-      break;
-    }
-    default:
-    {
-      ERROR ("plugin_notification_meta_add: Unknown type: %i", type);
-      sfree (meta);
+  switch (type) {
+  case NM_TYPE_STRING: {
+    meta->nm_value.nm_string = strdup((const char *)value);
+    if (meta->nm_value.nm_string == NULL) {
+      ERROR("plugin_notification_meta_add: strdup failed.");
+      sfree(meta);
       return (-1);
     }
+    break;
+  }
+  case NM_TYPE_SIGNED_INT: {
+    meta->nm_value.nm_signed_int = *((int64_t *)value);
+    break;
+  }
+  case NM_TYPE_UNSIGNED_INT: {
+    meta->nm_value.nm_unsigned_int = *((uint64_t *)value);
+    break;
+  }
+  case NM_TYPE_DOUBLE: {
+    meta->nm_value.nm_double = *((double *)value);
+    break;
+  }
+  case NM_TYPE_BOOLEAN: {
+    meta->nm_value.nm_boolean = *((_Bool *)value);
+    break;
+  }
+  default: {
+    ERROR("plugin_notification_meta_add: Unknown type: %i", type);
+    sfree(meta);
+    return (-1);
+  }
   } /* switch (type) */
 
   meta->next = NULL;
   tail = n->meta;
   while ((tail != NULL) && (tail->next != NULL))
     tail = tail->next;
