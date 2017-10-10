 		const char *path = p->one->path;
 		switch (fix_unmerged_status(p, data)) {
 		default:
 			die(_("unexpected diff status %c"), p->status);
 		case DIFF_STATUS_MODIFIED:
 		case DIFF_STATUS_TYPE_CHANGED:
-			if (add_file_to_index(&the_index, path, data->flags)) {
+			if (add_file_to_index(&the_index, path,
+					data->flags, data->force_mode)) {
 				if (!(data->flags & ADD_CACHE_IGNORE_ERRORS))
 					die(_("updating files failed"));
 				data->add_errors++;
 			}
 			break;
 		case DIFF_STATUS_DELETED:
