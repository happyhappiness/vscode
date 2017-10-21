 			+ (mergelist_cnt-1) * sizeof (filter_rule_list));
 	if (!push)
 		out_of_memory("push_local_filters");
 
 	push->mergelist_cnt = mergelist_cnt;
 	for (i = 0; i < mergelist_cnt; i++) {
-		memcpy(&push->mergelists[i], mergelist_parents[i]->u.mergelist,
-		       sizeof (filter_rule_list));
+		filter_rule *ex = mergelist_parents[i];
+		if (!ex)
+			continue;
+		memcpy(&push->mergelists[i], ex->u.mergelist, sizeof (filter_rule_list));
 	}
 
 	/* Note: parse_filter_file() might increase mergelist_cnt, so keep
 	 * this loop separate from the above loop. */
 	for (i = 0; i < mergelist_cnt; i++) {
 		filter_rule *ex = mergelist_parents[i];
-		filter_rule_list *lp = ex->u.mergelist;
+		filter_rule_list *lp;
+		if (!ex)
+			continue;
+		lp = ex->u.mergelist;
 
 		if (DEBUG_GTE(FILTER, 2)) {
 			rprintf(FINFO, "[%s] pushing mergelist #%d%s\n",
 				who_am_i(), i, lp->debug_type);
 		}
 
