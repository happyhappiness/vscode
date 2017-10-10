
static const char tag_template_nocleanup[] =
	N_("\nWrite a message for tag:\n  %s\n"
	"Lines starting with '%c' will be kept; you may remove them"
	" yourself if you want to.\n");

/* Parse arg given and add it the ref_sorting array */
static int parse_sorting_string(const char *arg, struct ref_sorting **sorting_tail)
{
	struct ref_sorting *s;
	int len;

	s = xcalloc(1, sizeof(*s));
	s->next = *sorting_tail;
	*sorting_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	if (skip_prefix(arg, "version:", &arg) ||
	    skip_prefix(arg, "v:", &arg))
		s->version = 1;

	len = strlen(arg);
	s->atom = parse_ref_filter_atom(arg, arg+len);

	return 0;
}

static int git_tag_config(const char *var, const char *value, void *cb)
{
	int status;
	struct ref_sorting **sorting_tail = (struct ref_sorting **)cb;

	if (!strcmp(var, "tag.sort")) {
		if (!value)
			return config_error_nonbool(var);
		parse_sorting_string(value, sorting_tail);
		return 0;
	}

	status = git_gpg_config(var, value, cb);
	if (status)
		return status;
