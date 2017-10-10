/*****************************************************************
 * Index File I/O
 *****************************************************************/

#define INDEX_FORMAT_DEFAULT 3

static int index_format_config(const char *var, const char *value, void *cb)
{
	unsigned int *version = cb;
	if (!strcmp(var, "index.version")) {
		*version = git_config_int(var, value);
		return 0;
	}
	return 1;
}

static unsigned int get_index_format_default(void)
{
	char *envversion = getenv("GIT_INDEX_VERSION");
	char *endp;
	unsigned int version = INDEX_FORMAT_DEFAULT;

	if (!envversion) {
		git_config(index_format_config, &version);
		if (version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < version) {
			warning(_("index.version set, but the value is invalid.\n"
				  "Using version %i"), INDEX_FORMAT_DEFAULT);
			return INDEX_FORMAT_DEFAULT;
		}
		return version;
