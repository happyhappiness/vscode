				 "%s%.*s", comment_line_string,
				 (int)(ep - cp), cp);
	if (s->display_comment_prefix)
		color_fprintf_ln(s->fp, color(WT_STATUS_HEADER, s), "%c",
				 comment_line_char);
	else
		fprintf_ln(s->fp, "");
}

static int has_unmerged(struct wt_status *s)
{
	int i;

