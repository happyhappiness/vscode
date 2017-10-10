 			    sha1_to_hex(merge_filter_ref));
 
 		filter->object.flags |= UNINTERESTING;
 		add_pending_object(&ref_list.revs,
 				   (struct object *) filter, "");
 		ref_list.revs.limited = 1;
-		prepare_revision_walk(&ref_list.revs);
+
+		if (prepare_revision_walk(&ref_list.revs))
+			die(_("revision walk setup failed"));
+
+		for (i = 0; i < ref_list.index; i++) {
+			struct ref_item *item = &ref_list.list[i];
+			struct commit *commit = item->commit;
+			int is_merged = !!(commit->object.flags & UNINTERESTING);
+			item->ignore = is_merged != (merge_filter == SHOW_MERGED);
+		}
+
+		for (i = 0; i < ref_list.index; i++) {
+			struct ref_item *item = &ref_list.list[i];
+			clear_commit_marks(item->commit, ALL_REV_FLAGS);
+		}
+		clear_commit_marks(filter, ALL_REV_FLAGS);
+
 		if (verbose)
 			ref_list.maxwidth = calc_maxwidth(&ref_list);
 	}
 
 	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);
 
