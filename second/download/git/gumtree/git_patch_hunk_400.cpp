 
 	if (nr_deltas && n > 1) {
 		unsigned nr_done = 0;
 		if (progress)
 			progress_state = start_progress(_("Compressing objects"),
 							nr_deltas);
-		qsort(delta_list, n, sizeof(*delta_list), type_size_sort);
+		QSORT(delta_list, n, type_size_sort);
 		ll_find_deltas(delta_list, n, window+1, depth, &nr_done);
 		stop_progress(&progress_state);
 		if (nr_done != nr_deltas)
 			die("inconsistency with delta count");
 	}
 	free(delta_list);
