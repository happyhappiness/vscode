write_err_out:
	ret = write_error(get_lock_file_path(lock));
	goto out_free;

}

int git_config_set_multivar(const char *key, const char *value,
			const char *value_regex, int multi_replace)
{
	return git_config_set_multivar_in_file(NULL, key, value, value_regex,
					       multi_replace);
}

static int section_name_match (const char *buf, const char *name)
{
	int i = 0, j = 0, dot = 0;
	if (buf[i] != '[')
