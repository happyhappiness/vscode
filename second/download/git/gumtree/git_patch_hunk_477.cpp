 	    : 0)
 		argv_array_push(&cmd.args, "--strict");
 
 	cmd.in = demux.out;
 	cmd.git_cmd = 1;
 	if (start_command(&cmd))
-		die("fetch-pack: unable to fork off %s", cmd_name);
+		die(_("fetch-pack: unable to fork off %s"), cmd_name);
 	if (do_keep && pack_lockfile) {
 		*pack_lockfile = index_pack_lockfile(cmd.out);
 		close(cmd.out);
 	}
 
 	if (!use_sideband)
