
struct branch {
	const char *name;
	const char *refname;

	const char *remote_name;
	struct remote *remote;

	const char **merge_name;
	struct refspec **merge;
	int merge_nr;
	int merge_alloc;
};

struct branch *branch_get(const char *name);

int branch_has_merge_config(struct branch *branch);
int branch_merge_matches(struct branch *, int n, const char *);

/* Flags to match_refs. */
enum match_refs_flags {
	MATCH_REFS_NONE		= 0,
	MATCH_REFS_ALL 		= (1 << 0),
	MATCH_REFS_MIRROR	= (1 << 1),
	MATCH_REFS_PRUNE	= (1 << 2),
	MATCH_REFS_FOLLOW_TAGS	= (1 << 3)
};

/* Reporting of tracking info */
int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs);
int format_tracking_info(struct branch *branch, struct strbuf *sb);

struct ref *get_local_heads(void);
/*
 * Find refs from a list which are likely to be pointed to by the given HEAD
 * ref. If 'all' is false, returns the most likely ref; otherwise, returns a
