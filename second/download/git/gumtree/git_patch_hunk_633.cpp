 		rollback_lock_file(&head_lock);
 		return error(_("failed to finalize '%s'."), git_path_head_file());
 	}
 	return 0;
 }
 
+static int rollback_is_safe(void)
+{
+	struct strbuf sb = STRBUF_INIT;
+	struct object_id expected_head, actual_head;
+
+	if (strbuf_read_file(&sb, git_path_abort_safety_file(), 0) >= 0) {
+		strbuf_trim(&sb);
+		if (get_oid_hex(sb.buf, &expected_head)) {
+			strbuf_release(&sb);
+			die(_("could not parse %s"), git_path_abort_safety_file());
+		}
+		strbuf_release(&sb);
+	}
+	else if (errno == ENOENT)
+		oidclr(&expected_head);
+	else
+		die_errno(_("could not read '%s'"), git_path_abort_safety_file());
+
+	if (get_oid("HEAD", &actual_head))
+		oidclr(&actual_head);
+
+	return !oidcmp(&actual_head, &expected_head);
+}
+
 static int reset_for_rollback(const unsigned char *sha1)
 {
 	const char *argv[4];	/* reset --merge <arg> + NULL */
+
 	argv[0] = "reset";
 	argv[1] = "--merge";
 	argv[2] = sha1_to_hex(sha1);
 	argv[3] = NULL;
 	return run_command_v_opt(argv, RUN_GIT_CMD);
 }
