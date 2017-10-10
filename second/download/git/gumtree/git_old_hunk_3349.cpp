				path = xstrfmt("%.*s/kfmclient", (int)len, path);
			filename = basename((char *)path);
		} else
			path = "kfmclient";
		strbuf_addf(&man_page, "man:%s(1)", page);
		execlp(path, filename, "newTab", man_page.buf, (char *)NULL);
		warning(_("failed to exec '%s': %s"), path, strerror(errno));
	}
}

static void exec_man_man(const char *path, const char *page)
{
	if (!path)
		path = "man";
	execlp(path, "man", page, (char *)NULL);
	warning(_("failed to exec '%s': %s"), path, strerror(errno));
}

static void exec_man_cmd(const char *cmd, const char *page)
{
	struct strbuf shell_cmd = STRBUF_INIT;
	strbuf_addf(&shell_cmd, "%s %s", cmd, page);
	execl(SHELL_PATH, SHELL_PATH, "-c", shell_cmd.buf, (char *)NULL);
	warning(_("failed to exec '%s': %s"), cmd, strerror(errno));
}

static void add_man_viewer(const char *name)
{
	struct man_viewer_list **p = &man_viewer_list;

