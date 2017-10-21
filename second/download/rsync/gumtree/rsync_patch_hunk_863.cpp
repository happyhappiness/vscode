 			rprintf(FERROR,
 			    "--prune-empty-dirs requires protocol 29 or higher"
 			    " (negotiated %d).\n",
 			    protocol_version);
 			exit_cleanup(RERR_PROTOCOL);
 		}
+	} else if (protocol_version >= 30) {
+		int compat_flags;
+		if (am_server) {
+			compat_flags = allow_inc_recurse ? CF_INC_RECURSE : 0;
+#if defined HAVE_LUTIMES && defined HAVE_UTIMES
+			compat_flags |= CF_SYMLINK_TIMES;
+#endif
+			write_byte(f_out, compat_flags);
+		} else
+			compat_flags = read_byte(f_in);
+		/* The inc_recurse var MUST be set to 0 or 1. */
+		inc_recurse = compat_flags & CF_INC_RECURSE ? 1 : 0;
+		if (am_sender) {
+			receiver_symlink_times = am_server
+			    ? strchr(client_info, 'L') != NULL
+			    : !!(compat_flags & CF_SYMLINK_TIMES);
+		}
+#if defined HAVE_LUTIMES && defined HAVE_UTIMES
+		else
+			receiver_symlink_times = 1;
+#endif
+		if (inc_recurse && !allow_inc_recurse) {
+			/* This should only be able to happen in a batch. */
+			fprintf(stderr,
+			    "Incompatible options specified for inc-recursive %s.\n",
+			    read_batch ? "batch file" : "connection");
+			exit_cleanup(RERR_SYNTAX);
+		}
+		need_messages_from_generator = 1;
+	}
+
+	if (need_unsorted_flist && (!am_sender || inc_recurse))
+		unsort_ndx = ++file_extra_cnt;
+
+	if (partial_dir && *partial_dir != '/' && (!am_server || local_server)) {
+		int flags = MATCHFLG_NO_PREFIXES | MATCHFLG_DIRECTORY;
+		if (!am_sender || protocol_version >= 30)
+			flags |= MATCHFLG_PERISHABLE;
+		parse_rule(&filter_list, partial_dir, flags, 0);
+	}
+
+
+#ifdef ICONV_OPTION
+	if (protect_args && files_from) {
+		if (am_sender)
+			filesfrom_convert = filesfrom_host && ic_send != (iconv_t)-1;
+		else
+			filesfrom_convert = !filesfrom_host && ic_recv != (iconv_t)-1;
 	}
+#endif
 
 	if (am_server) {
 		if (!checksum_seed)
 			checksum_seed = time(NULL);
 		write_int(f_out, checksum_seed);
 	} else {
