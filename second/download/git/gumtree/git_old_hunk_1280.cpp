
	if (!strcmp(var, "grep.threads")) {
		num_threads = git_config_int(var, value);
		if (num_threads < 0)
			die(_("invalid number of threads specified (%d) for %s"),
			    num_threads, var);
	}

	return st;
}

static void *lock_and_read_oid_file(const struct object_id *oid, enum object_type *type, unsigned long *size)
{
	void *data;
