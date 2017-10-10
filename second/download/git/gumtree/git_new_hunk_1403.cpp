}

#define CAP_CLEAN    (1u<<0)
#define CAP_SMUDGE   (1u<<1)

struct cmd2process {
	struct subprocess_entry subprocess; /* must be the first member! */
	unsigned int supported_capabilities;
};

static int subprocess_map_initialized;
static struct hashmap subprocess_map;

static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
{
	int err;
	struct cmd2process *entry = (struct cmd2process *)subprocess;
	struct string_list cap_list = STRING_LIST_INIT_NODUP;
	char *cap_buf;
	const char *cap_name;
	struct child_process *process = &subprocess->process;
	const char *cmd = subprocess->cmd;

	sigchain_push(SIGPIPE, SIG_IGN);

	err = packet_writel(process->in, "git-filter-client", "version=2", NULL);
	if (err)
		goto done;

	err = strcmp(packet_read_line(process->out, NULL), "git-filter-server");
	if (err) {
		error("external filter '%s' does not support filter protocol version 2", cmd);
