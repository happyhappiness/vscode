
static const char tag_template_nocleanup[] =
	N_("\nWrite a message for tag:\n  %s\n"
	"Lines starting with '%c' will be kept; you may remove them"
	" yourself if you want to.\n");

/*
 * Parse a sort string, and return 0 if parsed successfully. Will return
 * non-zero when the sort string does not parse into a known type. If var is
 * given, the error message becomes a warning and includes information about
 * the configuration value.
 */
static int parse_sort_string(const char *var, const char *arg, int *sort)
{
	int type = 0, flags = 0;

	if (skip_prefix(arg, "-", &arg))
		flags |= REVERSE_SORT;

	if (skip_prefix(arg, "version:", &arg) || skip_prefix(arg, "v:", &arg))
		type = VERCMP_SORT;
	else
		type = STRCMP_SORT;

	if (strcmp(arg, "refname")) {
		if (!var)
			return error(_("unsupported sort specification '%s'"), arg);
		else {
			warning(_("unsupported sort specification '%s' in variable '%s'"),
				var, arg);
			return -1;
		}
	}

	*sort = (type | flags);

	return 0;
}

static int git_tag_config(const char *var, const char *value, void *cb)
{
	int status;

	if (!strcmp(var, "tag.sort")) {
		if (!value)
			return config_error_nonbool(var);
		parse_sort_string(var, value, &tag_sort);
		return 0;
	}

	status = git_gpg_config(var, value, cb);
	if (status)
		return status;
