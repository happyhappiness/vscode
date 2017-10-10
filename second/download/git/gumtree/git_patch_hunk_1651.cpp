 		git_config_string_dup(&opts->strategy, key, value);
 	else if (!strcmp(key, "options.gpg-sign"))
 		git_config_string_dup(&opts->gpg_sign, key, value);
 	else if (!strcmp(key, "options.strategy-option")) {
 		ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
 		opts->xopts[opts->xopts_nr++] = xstrdup(value);
-	} else
+	} else if (!strcmp(key, "options.allow-rerere-auto"))
+		opts->allow_rerere_auto =
+			git_config_bool_or_int(key, value, &error_flag) ?
+				RERERE_AUTOUPDATE : RERERE_NOAUTOUPDATE;
+	else
 		return error(_("invalid key: %s"), key);
 
 	if (!error_flag)
 		return error(_("invalid value for %s: %s"), key, value);
 
 	return 0;
