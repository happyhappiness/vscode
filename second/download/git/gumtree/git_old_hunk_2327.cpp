		return;
	die("ambiguous argument '%s': both revision and filename\n"
	    "Use '--' to separate paths from revisions, like this:\n"
	    "'git <command> [<revision>...] -- [<file>...]'", arg);
}


/*
 * Test if it looks like we're at a git directory.
 * We want to see:
 *
 *  - either an objects/ directory _or_ the proper
