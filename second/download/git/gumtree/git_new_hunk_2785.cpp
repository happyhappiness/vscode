	if (git_config_rename_section(oldsection.buf, newsection.buf) < 0)
		die(_("Branch is renamed, but update of config-file failed"));
	strbuf_release(&oldsection);
	strbuf_release(&newsection);
}

static const char edit_description[] = "BRANCH_DESCRIPTION";

static int edit_branch_description(const char *branch_name)
{
	int status;
	struct strbuf buf = STRBUF_INIT;
