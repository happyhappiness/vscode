 	if (read_author_script(state) < 0)
 		die(_("could not parse author script"));
 
 	read_commit_msg(state);
 
 	if (read_state_file(&sb, state, "original-commit", 1) < 0)
-		hashclr(state->orig_commit);
-	else if (get_sha1_hex(sb.buf, state->orig_commit) < 0)
+		oidclr(&state->orig_commit);
+	else if (get_oid_hex(sb.buf, &state->orig_commit) < 0)
 		die(_("could not parse %s"), am_path(state, "original-commit"));
 
 	read_state_file(&sb, state, "threeway", 1);
 	state->threeway = !strcmp(sb.buf, "t");
 
 	read_state_file(&sb, state, "quiet", 1);
