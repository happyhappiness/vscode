 		ret = 1;
 
 	free(gitdir);
 	return ret;
 }
 
+/*
+ * Dies if the provided 'prefix' corresponds to an unpopulated submodule
+ */
+void die_in_unpopulated_submodule(const struct index_state *istate,
+				  const char *prefix)
+{
+	int i, prefixlen;
+
+	if (!prefix)
+		return;
+
+	prefixlen = strlen(prefix);
+
+	for (i = 0; i < istate->cache_nr; i++) {
+		struct cache_entry *ce = istate->cache[i];
+		int ce_len = ce_namelen(ce);
+
+		if (!S_ISGITLINK(ce->ce_mode))
+			continue;
+		if (prefixlen <= ce_len)
+			continue;
+		if (strncmp(ce->name, prefix, ce_len))
+			continue;
+		if (prefix[ce_len] != '/')
+			continue;
+
+		die(_("in unpopulated submodule '%s'"), ce->name);
+	}
+}
+
+/*
+ * Dies if any paths in the provided pathspec descends into a submodule
+ */
+void die_path_inside_submodule(const struct index_state *istate,
+			       const struct pathspec *ps)
+{
+	int i, j;
+
+	for (i = 0; i < istate->cache_nr; i++) {
+		struct cache_entry *ce = istate->cache[i];
+		int ce_len = ce_namelen(ce);
+
+		if (!S_ISGITLINK(ce->ce_mode))
+			continue;
+
+		for (j = 0; j < ps->nr ; j++) {
+			const struct pathspec_item *item = &ps->items[j];
+
+			if (item->len <= ce_len)
+				continue;
+			if (item->match[ce_len] != '/')
+				continue;
+			if (strncmp(ce->name, item->match, ce_len))
+				continue;
+			if (item->len == ce_len + 1)
+				continue;
+
+			die(_("Pathspec '%s' is in submodule '%.*s'"),
+			    item->original, ce_len, ce->name);
+		}
+	}
+}
+
 int parse_submodule_update_strategy(const char *value,
 		struct submodule_update_strategy *dst)
 {
 	free((void*)dst->command);
 	dst->command = NULL;
 	if (!strcmp(value, "none"))
