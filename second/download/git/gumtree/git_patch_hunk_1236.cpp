 		anchor = top + 1;
 	}
 	sort_and_merge_range_set(&ranges);
 
 	for (range_i = ranges.nr; range_i > 0; --range_i) {
 		const struct range *r = &ranges.ranges[range_i - 1];
-		long bottom = r->start;
-		long top = r->end;
-		struct blame_entry *next = ent;
-		ent = xcalloc(1, sizeof(*ent));
-		ent->lno = bottom;
-		ent->num_lines = top - bottom;
-		ent->suspect = o;
-		ent->s_lno = bottom;
-		ent->next = next;
-		origin_incref(o);
+		ent = blame_entry_prepend(ent, r->start, r->end, o);
 	}
 
 	o->suspects = ent;
 	prio_queue_put(&sb.commits, o->commit);
 
-	origin_decref(o);
+	blame_origin_decref(o);
 
 	range_set_release(&ranges);
 	string_list_clear(&range_list, 0);
 
 	sb.ent = NULL;
 	sb.path = path;
 
+	if (blame_move_score)
+		sb.move_score = blame_move_score;
+	if (blame_copy_score)
+		sb.copy_score = blame_copy_score;
+
+	sb.debug = DEBUG;
+	sb.on_sanity_fail = &sanity_check_on_fail;
+
+	sb.show_root = show_root;
+	sb.xdl_opts = xdl_opts;
+	sb.no_whole_file_rename = no_whole_file_rename;
+
 	read_mailmap(&mailmap, NULL);
 
+	sb.found_guilty_entry = &found_guilty_entry;
+	sb.found_guilty_entry_data = &pi;
+	if (show_progress)
+		pi.progress = start_progress_delay(_("Blaming lines"),
+						   sb.num_lines, 50, 1);
+
 	assign_blame(&sb, opt);
 
+	stop_progress(&pi.progress);
+
 	if (!incremental)
 		setup_pager();
-
-	free(final_commit_name);
-
-	if (incremental)
+	else
 		return 0;
 
-	sb.ent = blame_sort(sb.ent, compare_blame_final);
+	blame_sort_final(&sb);
 
-	coalesce(&sb);
+	blame_coalesce(&sb);
 
 	if (!(output_option & OUTPUT_PORCELAIN))
 		find_alignment(&sb, &output_option);
 
 	output(&sb, output_option);
 	free((void *)sb.final_buf);
