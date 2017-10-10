		for (i = 0; i < skipped.nr; i++)
			fprintf(stderr, "  git branch -d %s\n",
				skipped.items[i].string);
	}
	string_list_clear(&skipped, 0);

	if (!result) {
		strbuf_addf(&buf, "remote.%s", remote->name);
		if (git_config_rename_section(buf.buf, NULL) < 1)
			return error(_("Could not remove config section '%s'"), buf.buf);
	}

	return result;
}

static void clear_push_info(void *util, const char *string)
{
	struct push_info *info = util;
