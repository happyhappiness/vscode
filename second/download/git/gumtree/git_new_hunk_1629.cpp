	strbuf_release(&nbuf);
	return !err;
}

#define CAP_CLEAN    (1u<<0)
#define CAP_SMUDGE   (1u<<1)
#define CAP_DELAY    (1u<<2)

struct cmd2process {
	struct subprocess_entry subprocess; /* must be the first member! */
	unsigned int supported_capabilities;
};

static int subprocess_map_initialized;
static struct hashmap subprocess_map;

static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
{
	static int versions[] = {2, 0};
	static struct subprocess_capability capabilities[] = {
		{ "clean",  CAP_CLEAN  },
		{ "smudge", CAP_SMUDGE },
		{ "delay",  CAP_DELAY  },
		{ NULL, 0 }
	};
	struct cmd2process *entry = (struct cmd2process *)subprocess;
	return subprocess_handshake(subprocess, "git-filter", versions, NULL,
				    capabilities,
				    &entry->supported_capabilities);
}

static void handle_filter_error(const struct strbuf *filter_status,
				struct cmd2process *entry,
				const unsigned int wanted_capability) {
	if (!strcmp(filter_status->buf, "error"))
		; /* The filter signaled a problem with the file. */
	else if (!strcmp(filter_status->buf, "abort") && wanted_capability) {
		/*
		 * The filter signaled a permanent problem. Don't try to filter
		 * files with the same command for the lifetime of the current
		 * Git process.
		 */
		 entry->supported_capabilities &= ~wanted_capability;
	} else {
		/*
		 * Something went wrong with the protocol filter.
		 * Force shutdown and restart if another blob requires filtering.
		 */
		error("external filter '%s' failed", entry->subprocess.cmd);
		subprocess_stop(&subprocess_map, &entry->subprocess);
		free(entry);
	}
}

static int apply_multi_file_filter(const char *path, const char *src, size_t len,
				   int fd, struct strbuf *dst, const char *cmd,
				   const unsigned int wanted_capability,
				   struct delayed_checkout *dco)
{
	int err;
	int can_delay = 0;
	struct cmd2process *entry;
	struct child_process *process;
	struct strbuf nbuf = STRBUF_INIT;
	struct strbuf filter_status = STRBUF_INIT;
	const char *filter_type;

