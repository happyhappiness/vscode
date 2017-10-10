	if (!git_configset_get_value(cs, key, &value))
		return git_config_pathname(dest, key, value);
	else
		return 1;
}

static void git_config_check_init(void)
{
	if (the_config_set.hash_initialized)
		return;
	git_configset_init(&the_config_set);
	git_config_raw(config_set_callback, &the_config_set);
}

void git_config_clear(void)
{
	if (!the_config_set.hash_initialized)
		return;
	git_configset_clear(&the_config_set);
}

int git_config_get_value(const char *key, const char **value)
{
	git_config_check_init();
	return git_configset_get_value(&the_config_set, key, value);
}

const struct string_list *git_config_get_value_multi(const char *key)
{
	git_config_check_init();
	return git_configset_get_value_multi(&the_config_set, key);
}

int git_config_get_string_const(const char *key, const char **dest)
{
	int ret;
	git_config_check_init();
	ret = git_configset_get_string_const(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

int git_config_get_string(const char *key, char **dest)
{
	git_config_check_init();
	return git_config_get_string_const(key, (const char **)dest);
}

int git_config_get_int(const char *key, int *dest)
{
	git_config_check_init();
	return git_configset_get_int(&the_config_set, key, dest);
}

int git_config_get_ulong(const char *key, unsigned long *dest)
{
	git_config_check_init();
	return git_configset_get_ulong(&the_config_set, key, dest);
}

int git_config_get_bool(const char *key, int *dest)
{
	git_config_check_init();
	return git_configset_get_bool(&the_config_set, key, dest);
}

int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest)
{
	git_config_check_init();
	return git_configset_get_bool_or_int(&the_config_set, key, is_bool, dest);
}

int git_config_get_maybe_bool(const char *key, int *dest)
{
	git_config_check_init();
	return git_configset_get_maybe_bool(&the_config_set, key, dest);
}

int git_config_get_pathname(const char *key, const char **dest)
{
	int ret;
	git_config_check_init();
	ret = git_configset_get_pathname(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

int git_config_get_expiry(const char *key, const char **output)
{
	int ret = git_config_get_string_const(key, output);
	if (ret)
		return ret;
	if (strcmp(*output, "now")) {
		unsigned long now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
	return ret;
}

