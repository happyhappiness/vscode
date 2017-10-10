		}
	} else if (!strcmp(item.buf, "fetchrecursesubmodules")) {
		/* when parsing worktree configurations we can die early */
		int die_on_error = is_null_sha1(me->gitmodules_sha1);
		if (!me->overwrite &&
		    submodule->fetch_recurse != RECURSE_SUBMODULES_NONE)
			warn_multiple_config(me->commit_sha1, submodule->name,
					"fetchrecursesubmodules");
		else
			submodule->fetch_recurse = parse_fetch_recurse(
								var, value,
								die_on_error);
	} else if (!strcmp(item.buf, "ignore")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (!me->overwrite && submodule->ignore)
			warn_multiple_config(me->commit_sha1, submodule->name,
					"ignore");
		else if (strcmp(value, "untracked") &&
			 strcmp(value, "dirty") &&
			 strcmp(value, "all") &&
			 strcmp(value, "none"))
			warning("Invalid parameter '%s' for config option "
