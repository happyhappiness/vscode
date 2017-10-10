					&cb);
		free(ref);
	}
	return status;
}

/*
 * main "reflog"
 */

static const char reflog_usage[] =
"git reflog [ show | expire | delete ]";

int cmd_reflog(int argc, const char **argv, const char *prefix)
{
	if (argc > 1 && !strcmp(argv[1], "-h"))
		usage(reflog_usage);

