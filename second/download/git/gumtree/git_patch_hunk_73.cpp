 		ent->num_lines = top - bottom;
 		ent->suspect = o;
 		ent->s_lno = bottom;
 		ent->next = next;
 		origin_incref(o);
 	}
+
+	o->suspects = ent;
+	prio_queue_put(&sb.commits, o->commit);
+
 	origin_decref(o);
 
 	range_set_release(&ranges);
 	string_list_clear(&range_list, 0);
 
-	sb.ent = ent;
+	sb.ent = NULL;
 	sb.path = path;
 
 	read_mailmap(&mailmap, NULL);
 
 	if (!incremental)
 		setup_pager();
 
 	assign_blame(&sb, opt);
 
 	if (incremental)
 		return 0;
 
+	sb.ent = blame_sort(sb.ent, compare_blame_final);
+
 	coalesce(&sb);
 
 	if (!(output_option & OUTPUT_PORCELAIN))
 		find_alignment(&sb, &output_option);
 
 	output(&sb, output_option);
