		 * exit with the same code as die().
		 */
		exit(128);
}

static const char * const builtin_checkout_index_usage[] = {
	N_("git checkout-index [<options>] [--] [<file>...]"),
	NULL
};

static struct lock_file lock_file;

static int option_parse_u(const struct option *opt,
