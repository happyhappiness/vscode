 	fprintf(fp, "%c %s", comment_line_char, cut_line);
 	strbuf_add_commented_lines(&buf, explanation, strlen(explanation));
 	fputs(buf.buf, fp);
 	strbuf_release(&buf);
 }
 
-static void wt_status_print_verbose(struct wt_status *s)
+static void wt_longstatus_print_verbose(struct wt_status *s)
 {
 	struct rev_info rev;
 	struct setup_revision_opt opt;
 	int dirty_submodules;
 	const char *c = color(WT_STATUS_HEADER, s);
 
 	init_revisions(&rev, NULL);
 	DIFF_OPT_SET(&rev.diffopt, ALLOW_TEXTCONV);
+	rev.diffopt.ita_invisible_in_index = 1;
 
 	memset(&opt, 0, sizeof(opt));
 	opt.def = s->is_initial ? EMPTY_TREE_SHA1_HEX : s->reference;
 	setup_revisions(0, NULL, &rev, &opt);
 
 	rev.diffopt.output_format |= DIFF_FORMAT_PATCH;
