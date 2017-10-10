		return 0;
	}
	return git_default_config(var, value, cb);
}

/**
 * Appends merge candidates from FETCH_HEAD that are not marked not-for-merge
 * into merge_heads.
 */
static void get_merge_heads(struct sha1_array *merge_heads)
{
	const char *filename = git_path("FETCH_HEAD");
