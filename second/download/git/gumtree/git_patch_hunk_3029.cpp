 	int ret = 0;
 
 	/* this also ensures that we only parse submodule entries */
 	if (!name_and_item_from_var(var, &name, &item))
 		return 0;
 
-	submodule = lookup_or_create_by_name(me->cache, me->gitmodules_sha1,
-			name.buf);
+	submodule = lookup_or_create_by_name(me->cache,
+					     me->gitmodules_sha1,
+					     name.buf);
 
 	if (!strcmp(item.buf, "path")) {
-		struct strbuf path = STRBUF_INIT;
-		if (!value) {
+		if (!value)
 			ret = config_error_nonbool(var);
-			goto release_return;
-		}
-		if (!me->overwrite && submodule->path != NULL) {
+		else if (!me->overwrite && submodule->path != NULL)
 			warn_multiple_config(me->commit_sha1, submodule->name,
 					"path");
-			goto release_return;
+		else {
+			if (submodule->path)
+				cache_remove_path(me->cache, submodule);
+			free((void *) submodule->path);
+			submodule->path = xstrdup(value);
+			cache_put_path(me->cache, submodule);
 		}
-
-		if (submodule->path)
-			cache_remove_path(me->cache, submodule);
-		free((void *) submodule->path);
-		strbuf_addstr(&path, value);
-		submodule->path = strbuf_detach(&path, NULL);
-		cache_put_path(me->cache, submodule);
 	} else if (!strcmp(item.buf, "fetchrecursesubmodules")) {
 		/* when parsing worktree configurations we can die early */
 		int die_on_error = is_null_sha1(me->gitmodules_sha1);
 		if (!me->overwrite &&
-		    submodule->fetch_recurse != RECURSE_SUBMODULES_NONE) {
+		    submodule->fetch_recurse != RECURSE_SUBMODULES_NONE)
 			warn_multiple_config(me->commit_sha1, submodule->name,
 					"fetchrecursesubmodules");
-			goto release_return;
-		}
-
-		submodule->fetch_recurse = parse_fetch_recurse(var, value,
+		else
+			submodule->fetch_recurse = parse_fetch_recurse(
+								var, value,
 								die_on_error);
 	} else if (!strcmp(item.buf, "ignore")) {
-		struct strbuf ignore = STRBUF_INIT;
-		if (!me->overwrite && submodule->ignore != NULL) {
+		if (!value)
+			ret = config_error_nonbool(var);
+		else if (!me->overwrite && submodule->ignore != NULL)
 			warn_multiple_config(me->commit_sha1, submodule->name,
 					"ignore");
-			goto release_return;
-		}
-		if (!value) {
-			ret = config_error_nonbool(var);
-			goto release_return;
-		}
-		if (strcmp(value, "untracked") && strcmp(value, "dirty") &&
-		    strcmp(value, "all") && strcmp(value, "none")) {
+		else if (strcmp(value, "untracked") &&
+			 strcmp(value, "dirty") &&
+			 strcmp(value, "all") &&
+			 strcmp(value, "none"))
 			warning("Invalid parameter '%s' for config option "
 					"'submodule.%s.ignore'", value, var);
-			goto release_return;
+		else {
+			free((void *) submodule->ignore);
+			submodule->ignore = xstrdup(value);
 		}
-
-		free((void *) submodule->ignore);
-		strbuf_addstr(&ignore, value);
-		submodule->ignore = strbuf_detach(&ignore, NULL);
 	} else if (!strcmp(item.buf, "url")) {
-		struct strbuf url = STRBUF_INIT;
 		if (!value) {
 			ret = config_error_nonbool(var);
-			goto release_return;
-		}
-		if (!me->overwrite && submodule->url != NULL) {
+		} else if (!me->overwrite && submodule->url != NULL) {
 			warn_multiple_config(me->commit_sha1, submodule->name,
 					"url");
-			goto release_return;
+		} else {
+			free((void *) submodule->url);
+			submodule->url = xstrdup(value);
 		}
-
-		free((void *) submodule->url);
-		strbuf_addstr(&url, value);
-		submodule->url = strbuf_detach(&url, NULL);
 	}
 
-release_return:
 	strbuf_release(&name);
 	strbuf_release(&item);
 
 	return ret;
 }
 
