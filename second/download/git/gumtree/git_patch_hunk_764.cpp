 			submodule->ignore = xstrdup(value);
 		}
 	} else if (!strcmp(item.buf, "url")) {
 		if (!value) {
 			ret = config_error_nonbool(var);
 		} else if (!me->overwrite && submodule->url) {
-			warn_multiple_config(me->commit_sha1, submodule->name,
+			warn_multiple_config(me->treeish_name, submodule->name,
 					"url");
 		} else {
 			free((void *) submodule->url);
 			submodule->url = xstrdup(value);
 		}
 	} else if (!strcmp(item.buf, "update")) {
 		if (!value)
 			ret = config_error_nonbool(var);
 		else if (!me->overwrite &&
 			 submodule->update_strategy.type != SM_UPDATE_UNSPECIFIED)
-			warn_multiple_config(me->commit_sha1, submodule->name,
+			warn_multiple_config(me->treeish_name, submodule->name,
 					     "update");
 		else if (parse_submodule_update_strategy(value,
 			 &submodule->update_strategy) < 0)
 				die(_("invalid value for %s"), var);
 	} else if (!strcmp(item.buf, "shallow")) {
 		if (!me->overwrite && submodule->recommend_shallow != -1)
-			warn_multiple_config(me->commit_sha1, submodule->name,
+			warn_multiple_config(me->treeish_name, submodule->name,
 					     "shallow");
 		else
 			submodule->recommend_shallow =
 				git_config_bool(var, value);
 	} else if (!strcmp(item.buf, "branch")) {
 		if (!me->overwrite && submodule->branch)
-			warn_multiple_config(me->commit_sha1, submodule->name,
+			warn_multiple_config(me->treeish_name, submodule->name,
 					     "branch");
 		else {
 			free((void *)submodule->branch);
 			submodule->branch = xstrdup(value);
 		}
 	}
