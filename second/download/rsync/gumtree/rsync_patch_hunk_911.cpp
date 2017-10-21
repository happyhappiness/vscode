 			fprintf(stderr,
 			    "Incompatible options specified for inc-recursive %s.\n",
 			    read_batch ? "batch file" : "connection");
 			exit_cleanup(RERR_SYNTAX);
 		}
 		need_messages_from_generator = 1;
+#if defined HAVE_LUTIMES && defined HAVE_UTIMES
+	} else if (!am_sender) {
+		receiver_symlink_times = 1;
+#endif
 	}
 
 	if (need_unsorted_flist && (!am_sender || inc_recurse))
 		unsort_ndx = ++file_extra_cnt;
 
 	if (partial_dir && *partial_dir != '/' && (!am_server || local_server)) {
