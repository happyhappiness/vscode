			free((void *) submodule->ignore);
			submodule->ignore = xstrdup(value);
		}
	} else if (!strcmp(item.buf, "url")) {
		if (!value) {
			ret = config_error_nonbool(var);
		} else if (!me->overwrite && submodule->url != NULL) {
			warn_multiple_config(me->commit_sha1, submodule->name,
					"url");
		} else {
			free((void *) submodule->url);
			submodule->url = xstrdup(value);
		}
	}

	strbuf_release(&name);
	strbuf_release(&item);

	return ret;
