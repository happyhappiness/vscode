		return error("%s: %s", new_name, strerror(errno));
	}
	return 0;
}

/*
 * Check and apply the patch in-core; leave the result in patch->result
 * for the caller to write it out to the final destination.
 */
static int check_patch(struct patch *patch)
{
	struct stat st;
