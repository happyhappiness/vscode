
struct branch {
	const char *name;
	const char *refname;

	const char *remote_name;
	const char *pushremote_name;

	const char **merge_name;
	struct refspec **merge;
	int merge_nr;
	int merge_alloc;

	const char *push_tracking_ref;
};

struct branch *branch_get(const char *name);
const char *remote_for_branch(struct branch *branch, int *explicit);
const char *pushremote_for_branch(struct branch *branch, int *explicit);

int branch_has_merge_config(struct branch *branch);
int branch_merge_matches(struct branch *, int n, const char *);

/**
 * Return the fully-qualified refname of the tracking branch for `branch`.
 * I.e., what "branch@{upstream}" would give you. Returns NULL if no
 * upstream is defined.
 *
 * If `err` is not NULL and no upstream is defined, a more specific error
 * message is recorded there (if the function does not return NULL, then
 * `err` is not touched).
 */
const char *branch_get_upstream(struct branch *branch, struct strbuf *err);

/**
 * Return the tracking branch that corresponds to the ref we would push to
 * given a bare `git push` while `branch` is checked out.
 *
 * The return value and `err` conventions match those of `branch_get_upstream`.
 */
const char *branch_get_push(struct branch *branch, struct strbuf *err);

/* Flags to match_refs. */
enum match_refs_flags {
	MATCH_REFS_NONE		= 0,
	MATCH_REFS_ALL 		= (1 << 0),
	MATCH_REFS_MIRROR	= (1 << 1),
	MATCH_REFS_PRUNE	= (1 << 2),
	MATCH_REFS_FOLLOW_TAGS	= (1 << 3)
};

/* Reporting of tracking info */
int stat_tracking_info(struct branch *branch, int *num_ours, int *num_theirs,
		       const char **upstream_name);
int format_tracking_info(struct branch *branch, struct strbuf *sb);

struct ref *get_local_heads(void);
/*
 * Find refs from a list which are likely to be pointed to by the given HEAD
 * ref. If 'all' is false, returns the most likely ref; otherwise, returns a
