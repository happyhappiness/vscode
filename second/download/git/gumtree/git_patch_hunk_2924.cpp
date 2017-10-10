 			die("fetch-pack: unable to fork off sideband"
 			    " demultiplexer");
 	}
 	else
 		demux.out = xd[0];
 
-	cmd.argv = argv;
-	av = argv;
-	*hdr_arg = 0;
 	if (!args->keep_pack && unpack_limit) {
-		struct pack_header header;
 
 		if (read_pack_header(demux.out, &header))
 			die("protocol error: bad pack header");
-		snprintf(hdr_arg, sizeof(hdr_arg),
-			 "--pack_header=%"PRIu32",%"PRIu32,
-			 ntohl(header.hdr_version), ntohl(header.hdr_entries));
+		pass_header = 1;
 		if (ntohl(header.hdr_entries) < unpack_limit)
 			do_keep = 0;
 		else
 			do_keep = 1;
 	}
 
 	if (alternate_shallow_file) {
-		*av++ = "--shallow-file";
-		*av++ = alternate_shallow_file;
+		argv_array_push(&cmd.args, "--shallow-file");
+		argv_array_push(&cmd.args, alternate_shallow_file);
 	}
 
 	if (do_keep) {
 		if (pack_lockfile)
 			cmd.out = -1;
-		*av++ = cmd_name = "index-pack";
-		*av++ = "--stdin";
+		cmd_name = "index-pack";
+		argv_array_push(&cmd.args, cmd_name);
+		argv_array_push(&cmd.args, "--stdin");
 		if (!args->quiet && !args->no_progress)
-			*av++ = "-v";
+			argv_array_push(&cmd.args, "-v");
 		if (args->use_thin_pack)
-			*av++ = "--fix-thin";
+			argv_array_push(&cmd.args, "--fix-thin");
 		if (args->lock_pack || unpack_limit) {
-			int s = sprintf(keep_arg,
-					"--keep=fetch-pack %"PRIuMAX " on ", (uintmax_t) getpid());
-			if (gethostname(keep_arg + s, sizeof(keep_arg) - s))
-				strcpy(keep_arg + s, "localhost");
-			*av++ = keep_arg;
+			char hostname[256];
+			if (gethostname(hostname, sizeof(hostname)))
+				xsnprintf(hostname, sizeof(hostname), "localhost");
+			argv_array_pushf(&cmd.args,
+					"--keep=fetch-pack %"PRIuMAX " on %s",
+					(uintmax_t)getpid(), hostname);
 		}
 		if (args->check_self_contained_and_connected)
-			*av++ = "--check-self-contained-and-connected";
+			argv_array_push(&cmd.args, "--check-self-contained-and-connected");
 	}
 	else {
-		*av++ = cmd_name = "unpack-objects";
+		cmd_name = "unpack-objects";
+		argv_array_push(&cmd.args, cmd_name);
 		if (args->quiet || args->no_progress)
-			*av++ = "-q";
+			argv_array_push(&cmd.args, "-q");
 		args->check_self_contained_and_connected = 0;
 	}
-	if (*hdr_arg)
-		*av++ = hdr_arg;
+
+	if (pass_header)
+		argv_array_pushf(&cmd.args, "--pack_header=%"PRIu32",%"PRIu32,
+				 ntohl(header.hdr_version),
+				 ntohl(header.hdr_entries));
 	if (fetch_fsck_objects >= 0
 	    ? fetch_fsck_objects
 	    : transfer_fsck_objects >= 0
 	    ? transfer_fsck_objects
 	    : 0)
-		*av++ = "--strict";
-	*av++ = NULL;
+		argv_array_push(&cmd.args, "--strict");
 
 	cmd.in = demux.out;
 	cmd.git_cmd = 1;
 	if (start_command(&cmd))
 		die("fetch-pack: unable to fork off %s", cmd_name);
 	if (do_keep && pack_lockfile) {
