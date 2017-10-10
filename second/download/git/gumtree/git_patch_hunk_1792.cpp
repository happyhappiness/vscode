 	ret = git_config_early(fn, data, repo_config);
 	if (repo_config)
 		free(repo_config);
 	return ret;
 }
 
-int git_config(config_fn_t fn, void *data)
+static void git_config_raw(config_fn_t fn, void *data)
+{
+	if (git_config_with_options(fn, data, NULL, 1) < 0)
+		/*
+		 * git_config_with_options() normally returns only
+		 * positive values, as most errors are fatal, and
+		 * non-fatal potential errors are guarded by "if"
+		 * statements that are entered only when no error is
+		 * possible.
+		 *
+		 * If we ever encounter a non-fatal error, it means
+		 * something went really wrong and we should stop
+		 * immediately.
+		 */
+		die(_("unknown error occured while reading the configuration files"));
+}
+
+static void configset_iter(struct config_set *cs, config_fn_t fn, void *data)
+{
+	int i, value_index;
+	struct string_list *values;
+	struct config_set_element *entry;
+	struct configset_list *list = &cs->list;
+	struct key_value_info *kv_info;
+
+	for (i = 0; i < list->nr; i++) {
+		entry = list->items[i].e;
+		value_index = list->items[i].value_index;
+		values = &entry->value_list;
+		if (fn(entry->key, values->items[value_index].string, data) < 0) {
+			kv_info = values->items[value_index].util;
+			git_die_config_linenr(entry->key, kv_info->filename, kv_info->linenr);
+		}
+	}
+}
+
+static void git_config_check_init(void);
+
+void git_config(config_fn_t fn, void *data)
+{
+	git_config_check_init();
+	configset_iter(&the_config_set, fn, data);
+}
+
+static struct config_set_element *configset_find_element(struct config_set *cs, const char *key)
 {
-	return git_config_with_options(fn, data, NULL, 1);
+	struct config_set_element k;
+	struct config_set_element *found_entry;
+	char *normalized_key;
+	int ret;
+	/*
+	 * `key` may come from the user, so normalize it before using it
+	 * for querying entries from the hashmap.
+	 */
+	ret = git_config_parse_key(key, &normalized_key, NULL);
+
+	if (ret)
+		return NULL;
+
+	hashmap_entry_init(&k, strhash(normalized_key));
+	k.key = normalized_key;
+	found_entry = hashmap_get(&cs->config_hash, &k, NULL);
+	free(normalized_key);
+	return found_entry;
+}
+
+static int configset_add_value(struct config_set *cs, const char *key, const char *value)
+{
+	struct config_set_element *e;
+	struct string_list_item *si;
+	struct configset_list_item *l_item;
+	struct key_value_info *kv_info = xmalloc(sizeof(*kv_info));
+
+	e = configset_find_element(cs, key);
+	/*
+	 * Since the keys are being fed by git_config*() callback mechanism, they
+	 * are already normalized. So simply add them without any further munging.
+	 */
+	if (!e) {
+		e = xmalloc(sizeof(*e));
+		hashmap_entry_init(e, strhash(key));
+		e->key = xstrdup(key);
+		string_list_init(&e->value_list, 1);
+		hashmap_add(&cs->config_hash, e);
+	}
+	si = string_list_append_nodup(&e->value_list, value ? xstrdup(value) : NULL);
+
+	ALLOC_GROW(cs->list.items, cs->list.nr + 1, cs->list.alloc);
+	l_item = &cs->list.items[cs->list.nr++];
+	l_item->e = e;
+	l_item->value_index = e->value_list.nr - 1;
+
+	if (cf) {
+		kv_info->filename = strintern(cf->name);
+		kv_info->linenr = cf->linenr;
+	} else {
+		/* for values read from `git_config_from_parameters()` */
+		kv_info->filename = NULL;
+		kv_info->linenr = -1;
+	}
+	si->util = kv_info;
+
+	return 0;
+}
+
+static int config_set_element_cmp(const struct config_set_element *e1,
+				 const struct config_set_element *e2, const void *unused)
+{
+	return strcmp(e1->key, e2->key);
+}
+
+void git_configset_init(struct config_set *cs)
+{
+	hashmap_init(&cs->config_hash, (hashmap_cmp_fn)config_set_element_cmp, 0);
+	cs->hash_initialized = 1;
+	cs->list.nr = 0;
+	cs->list.alloc = 0;
+	cs->list.items = NULL;
+}
+
+void git_configset_clear(struct config_set *cs)
+{
+	struct config_set_element *entry;
+	struct hashmap_iter iter;
+	if (!cs->hash_initialized)
+		return;
+
+	hashmap_iter_init(&cs->config_hash, &iter);
+	while ((entry = hashmap_iter_next(&iter))) {
+		free(entry->key);
+		string_list_clear(&entry->value_list, 1);
+	}
+	hashmap_free(&cs->config_hash, 1);
+	cs->hash_initialized = 0;
+	free(cs->list.items);
+	cs->list.nr = 0;
+	cs->list.alloc = 0;
+	cs->list.items = NULL;
+}
+
+static int config_set_callback(const char *key, const char *value, void *cb)
+{
+	struct config_set *cs = cb;
+	configset_add_value(cs, key, value);
+	return 0;
+}
+
+int git_configset_add_file(struct config_set *cs, const char *filename)
+{
+	return git_config_from_file(config_set_callback, filename, cs);
+}
+
+int git_configset_get_value(struct config_set *cs, const char *key, const char **value)
+{
+	const struct string_list *values = NULL;
+	/*
+	 * Follows "last one wins" semantic, i.e., if there are multiple matches for the
+	 * queried key in the files of the configset, the value returned will be the last
+	 * value in the value list for that key.
+	 */
+	values = git_configset_get_value_multi(cs, key);
+
+	if (!values)
+		return 1;
+	assert(values->nr > 0);
+	*value = values->items[values->nr - 1].string;
+	return 0;
+}
+
+const struct string_list *git_configset_get_value_multi(struct config_set *cs, const char *key)
+{
+	struct config_set_element *e = configset_find_element(cs, key);
+	return e ? &e->value_list : NULL;
+}
+
+int git_configset_get_string_const(struct config_set *cs, const char *key, const char **dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value))
+		return git_config_string(dest, key, value);
+	else
+		return 1;
+}
+
+int git_configset_get_string(struct config_set *cs, const char *key, char **dest)
+{
+	return git_configset_get_string_const(cs, key, (const char **)dest);
+}
+
+int git_configset_get_int(struct config_set *cs, const char *key, int *dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value)) {
+		*dest = git_config_int(key, value);
+		return 0;
+	} else
+		return 1;
+}
+
+int git_configset_get_ulong(struct config_set *cs, const char *key, unsigned long *dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value)) {
+		*dest = git_config_ulong(key, value);
+		return 0;
+	} else
+		return 1;
+}
+
+int git_configset_get_bool(struct config_set *cs, const char *key, int *dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value)) {
+		*dest = git_config_bool(key, value);
+		return 0;
+	} else
+		return 1;
+}
+
+int git_configset_get_bool_or_int(struct config_set *cs, const char *key,
+				int *is_bool, int *dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value)) {
+		*dest = git_config_bool_or_int(key, value, is_bool);
+		return 0;
+	} else
+		return 1;
+}
+
+int git_configset_get_maybe_bool(struct config_set *cs, const char *key, int *dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value)) {
+		*dest = git_config_maybe_bool(key, value);
+		if (*dest == -1)
+			return -1;
+		return 0;
+	} else
+		return 1;
+}
+
+int git_configset_get_pathname(struct config_set *cs, const char *key, const char **dest)
+{
+	const char *value;
+	if (!git_configset_get_value(cs, key, &value))
+		return git_config_pathname(dest, key, value);
+	else
+		return 1;
+}
+
+static void git_config_check_init(void)
+{
+	if (the_config_set.hash_initialized)
+		return;
+	git_configset_init(&the_config_set);
+	git_config_raw(config_set_callback, &the_config_set);
+}
+
+void git_config_clear(void)
+{
+	if (!the_config_set.hash_initialized)
+		return;
+	git_configset_clear(&the_config_set);
+}
+
+int git_config_get_value(const char *key, const char **value)
+{
+	git_config_check_init();
+	return git_configset_get_value(&the_config_set, key, value);
+}
+
+const struct string_list *git_config_get_value_multi(const char *key)
+{
+	git_config_check_init();
+	return git_configset_get_value_multi(&the_config_set, key);
+}
+
+int git_config_get_string_const(const char *key, const char **dest)
+{
+	int ret;
+	git_config_check_init();
+	ret = git_configset_get_string_const(&the_config_set, key, dest);
+	if (ret < 0)
+		git_die_config(key, NULL);
+	return ret;
+}
+
+int git_config_get_string(const char *key, char **dest)
+{
+	git_config_check_init();
+	return git_config_get_string_const(key, (const char **)dest);
+}
+
+int git_config_get_int(const char *key, int *dest)
+{
+	git_config_check_init();
+	return git_configset_get_int(&the_config_set, key, dest);
+}
+
+int git_config_get_ulong(const char *key, unsigned long *dest)
+{
+	git_config_check_init();
+	return git_configset_get_ulong(&the_config_set, key, dest);
+}
+
+int git_config_get_bool(const char *key, int *dest)
+{
+	git_config_check_init();
+	return git_configset_get_bool(&the_config_set, key, dest);
+}
+
+int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest)
+{
+	git_config_check_init();
+	return git_configset_get_bool_or_int(&the_config_set, key, is_bool, dest);
+}
+
+int git_config_get_maybe_bool(const char *key, int *dest)
+{
+	git_config_check_init();
+	return git_configset_get_maybe_bool(&the_config_set, key, dest);
+}
+
+int git_config_get_pathname(const char *key, const char **dest)
+{
+	int ret;
+	git_config_check_init();
+	ret = git_configset_get_pathname(&the_config_set, key, dest);
+	if (ret < 0)
+		git_die_config(key, NULL);
+	return ret;
+}
+
+NORETURN
+void git_die_config_linenr(const char *key, const char *filename, int linenr)
+{
+	if (!filename)
+		die(_("unable to parse '%s' from command-line config"), key);
+	else
+		die(_("bad config variable '%s' in file '%s' at line %d"),
+		    key, filename, linenr);
+}
+
+NORETURN __attribute__((format(printf, 2, 3)))
+void git_die_config(const char *key, const char *err, ...)
+{
+	const struct string_list *values;
+	struct key_value_info *kv_info;
+
+	if (err) {
+		va_list params;
+		va_start(params, err);
+		vreportf("error: ", err, params);
+		va_end(params);
+	}
+	values = git_config_get_value_multi(key);
+	kv_info = values->items[values->nr - 1].util;
+	git_die_config_linenr(key, kv_info->filename, kv_info->linenr);
 }
 
 /*
  * Find all the stuff for git_config_set() below.
  */
 
