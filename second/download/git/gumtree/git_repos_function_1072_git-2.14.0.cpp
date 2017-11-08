void wt_status_prepare(struct wt_status *s)
{
	struct object_id oid;

	memset(s, 0, sizeof(*s));
	memcpy(s->color_palette, default_wt_status_colors,
	       sizeof(default_wt_status_colors));
	s->show_untracked_files = SHOW_NORMAL_UNTRACKED_FILES;
	s->use_color = -1;
	s->relative_paths = 1;
	s->branch = resolve_refdup("HEAD", 0, oid.hash, NULL);
	s->reference = "HEAD";
	s->fp = stdout;
	s->index_file = get_index_file();
	s->change.strdup_strings = 1;
	s->untracked.strdup_strings = 1;
	s->ignored.strdup_strings = 1;
	s->show_branch = -1;  /* unspecified */
	s->show_stash = 0;
	s->display_comment_prefix = 0;
}