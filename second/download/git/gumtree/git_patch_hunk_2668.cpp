 		if (!gitmodules_is_unmerged)
 			git_config_from_file(submodule_config, gitmodules_path.buf, NULL);
 		strbuf_release(&gitmodules_path);
 	}
 }
 
-int parse_submodule_config_option(const char *var, const char *value)
-{
-	struct string_list_item *config;
-	const char *name, *key;
-	int namelen;
-
-	if (parse_config_key(var, "submodule", &name, &namelen, &key) < 0 || !name)
-		return 0;
-
-	if (!strcmp(key, "path")) {
-		if (!value)
-			return config_error_nonbool(var);
-
-		config = unsorted_string_list_lookup(&config_name_for_path, value);
-		if (config)
-			free(config->util);
-		else
-			config = string_list_append(&config_name_for_path, xstrdup(value));
-		config->util = xmemdupz(name, namelen);
-	} else if (!strcmp(key, "fetchrecursesubmodules")) {
-		char *name_cstr = xmemdupz(name, namelen);
-		config = unsorted_string_list_lookup(&config_fetch_recurse_submodules_for_name, name_cstr);
-		if (!config)
-			config = string_list_append(&config_fetch_recurse_submodules_for_name, name_cstr);
-		else
-			free(name_cstr);
-		config->util = (void *)(intptr_t)parse_fetch_recurse_submodules_arg(var, value);
-	} else if (!strcmp(key, "ignore")) {
-		char *name_cstr;
-
-		if (!value)
-			return config_error_nonbool(var);
-
-		if (strcmp(value, "untracked") && strcmp(value, "dirty") &&
-		    strcmp(value, "all") && strcmp(value, "none")) {
-			warning("Invalid parameter \"%s\" for config option \"submodule.%s.ignore\"", value, var);
-			return 0;
-		}
-
-		name_cstr = xmemdupz(name, namelen);
-		config = unsorted_string_list_lookup(&config_ignore_for_name, name_cstr);
-		if (config) {
-			free(config->util);
-			free(name_cstr);
-		} else
-			config = string_list_append(&config_ignore_for_name, name_cstr);
-		config->util = xstrdup(value);
-		return 0;
-	}
-	return 0;
-}
-
 void handle_ignore_submodules_arg(struct diff_options *diffopt,
 				  const char *arg)
 {
 	DIFF_OPT_CLR(diffopt, IGNORE_SUBMODULES);
 	DIFF_OPT_CLR(diffopt, IGNORE_UNTRACKED_IN_SUBMODULES);
 	DIFF_OPT_CLR(diffopt, IGNORE_DIRTY_SUBMODULES);
