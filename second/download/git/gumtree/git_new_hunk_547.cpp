		die(_("staging updated .gitmodules failed"));
}

static int add_submodule_odb(const char *path)
{
	struct strbuf objects_directory = STRBUF_INIT;
	int ret = 0;

	ret = strbuf_git_path_submodule(&objects_directory, path, "objects/");
	if (ret)
		goto done;
	if (!is_directory(objects_directory.buf)) {
		ret = -1;
		goto done;
	}
	add_to_alternates_memory(objects_directory.buf);
done:
	strbuf_release(&objects_directory);
	return ret;
}

void set_diffopt_flags_from_submodule_config(struct diff_options *diffopt,
