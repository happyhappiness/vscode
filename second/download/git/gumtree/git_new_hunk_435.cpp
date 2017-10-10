	free(ce_3);
	return ret;
}

static void read_head_pointers(void)
{
	if (read_ref("HEAD", head_oid.hash))
		die("No HEAD -- no initial commit yet?");
	if (read_ref("MERGE_HEAD", merge_head_oid.hash)) {
		fprintf(stderr, "Not in the middle of a merge.\n");
		exit(0);
	}
}

static int do_unresolve(int ac, const char **av,
