void wt_status_get_state(struct wt_status_state *state, int get_detached_from);
int wt_status_check_rebase(const struct worktree *wt,
			   struct wt_status_state *state);
int wt_status_check_bisect(const struct worktree *wt,
			   struct wt_status_state *state);

__attribute__((format (printf, 3, 4)))
void status_printf_ln(struct wt_status *s, const char *color, const char *fmt, ...);
__attribute__((format (printf, 3, 4)))
void status_printf(struct wt_status *s, const char *color, const char *fmt, ...);

/* The following functions expect that the caller took care of reading the index. */
int has_unstaged_changes(int ignore_submodules);
int has_uncommitted_changes(int ignore_submodules);
int require_clean_work_tree(const char *action, const char *hint,
	int ignore_submodules, int gently);

#endif /* STATUS_H */
