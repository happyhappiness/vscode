		exit(1);
	else
		die("Needed a single revision");
}

static const char builtin_rev_parse_usage[] =
N_("git rev-parse --parseopt [options] -- [<args>...]\n"
   "   or: git rev-parse --sq-quote [<arg>...]\n"
   "   or: git rev-parse [options] [<arg>...]\n"
   "\n"
   "Run \"git rev-parse --parseopt -h\" for more information on the first usage.");

int cmd_rev_parse(int argc, const char **argv, const char *prefix)
{
	int i, as_is = 0, verify = 0, quiet = 0, revs_count = 0, type = 0;
