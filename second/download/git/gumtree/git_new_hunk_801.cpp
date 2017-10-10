		if (info->remote_name && !strcmp(info->remote_name, remote->name)) {
			const char *keys[] = { "remote", "merge", NULL }, **k;
			for (k = keys; *k; k++) {
				strbuf_reset(&buf);
				strbuf_addf(&buf, "branch.%s.%s",
						item->string, *k);
				result = git_config_set_gently(buf.buf, NULL);
				if (result && result != CONFIG_NOTHING_SET)
					die(_("could not unset '%s'"), buf.buf);
			}
		}
	}

	/*
	 * We cannot just pass a function to for_each_ref() which deletes
