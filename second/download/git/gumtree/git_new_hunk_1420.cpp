	if (check_refname_format(buf.buf, 0))
		die("bad git namespace path \"%s\"", raw_namespace);
	strbuf_addch(&buf, '/');
	return strbuf_detach(&buf, NULL);
}

void setup_git_env(void)
{
	const char *shallow_file;
	const char *replace_ref_base;

	if (getenv(NO_REPLACE_OBJECTS_ENVIRONMENT))
		check_replace_refs = 0;
	replace_ref_base = getenv(GIT_REPLACE_REF_BASE_ENVIRONMENT);
	git_replace_ref_base = xstrdup(replace_ref_base ? replace_ref_base
							  : "refs/replace/");
	namespace = expand_namespace(getenv(GIT_NAMESPACE_ENVIRONMENT));
	shallow_file = getenv(GIT_SHALLOW_FILE_ENVIRONMENT);
	if (shallow_file)
		set_alternate_shallow_file(shallow_file, 0);
}

int is_bare_repository(void)
