 	if (human_readable > 1 && argc == 2 && !am_server) {
 		/* Allow the old meaning of 'h' (--help) on its own. */
 		usage(FINFO);
 		exit_cleanup(0);
 	}
 
+	if (do_compression || def_compress_level != NOT_SPECIFIED) {
+		if (def_compress_level == NOT_SPECIFIED)
+			def_compress_level = Z_DEFAULT_COMPRESSION;
+		else if (def_compress_level < Z_DEFAULT_COMPRESSION || def_compress_level > Z_BEST_COMPRESSION) {
+			snprintf(err_buf, sizeof err_buf, "--compress-level value is invalid: %d\n",
+				 def_compress_level);
+			return 0;
+		} else if (def_compress_level == Z_NO_COMPRESSION)
+			do_compression = 0;
+		else if (!do_compression)
+			do_compression = 1;
+		if (do_compression && refused_compress) {
+			create_refuse_error(refused_compress);
+			return 0;
+		}
+#ifdef EXTERNAL_ZLIB
+		if (do_compression == 1) {
+			snprintf(err_buf, sizeof err_buf,
+				"This rsync lacks old-style --compress due to its external zlib.  Try -zz.\n");
+			if (am_server)
+				return 0;
+			fprintf(stderr, "%s" "Continuing without compression.\n\n", err_buf);
+			do_compression = 0;
+		}
+#endif
+	}
+
 #ifdef HAVE_SETVBUF
 	if (outbuf_mode && !am_server) {
 		int mode = *(uchar *)outbuf_mode;
 		if (islower(mode))
 			mode = toupper(mode);
 		fflush(stdout); /* Just in case... */
