 	case AUTOREBASE_ALWAYS:
 		return 1;
 	}
 	return 0;
 }
 
-void install_branch_config(int flag, const char *local, const char *origin, const char *remote)
+static const char tracking_advice[] =
+N_("\n"
+"After fixing the error cause you may try to fix up\n"
+"the remote tracking information by invoking\n"
+"\"git branch --set-upstream-to=%s%s%s\".");
+
+int install_branch_config(int flag, const char *local, const char *origin, const char *remote)
 {
 	const char *shortname = NULL;
 	struct strbuf key = STRBUF_INIT;
 	int rebasing = should_setup_rebase(origin);
 
 	if (skip_prefix(remote, "refs/heads/", &shortname)
 	    && !strcmp(local, shortname)
 	    && !origin) {
 		warning(_("Not setting branch %s as its own upstream."),
 			local);
-		return;
+		return 0;
 	}
 
 	strbuf_addf(&key, "branch.%s.remote", local);
-	git_config_set(key.buf, origin ? origin : ".");
+	if (git_config_set_gently(key.buf, origin ? origin : ".") < 0)
+		goto out_err;
 
 	strbuf_reset(&key);
 	strbuf_addf(&key, "branch.%s.merge", local);
-	git_config_set(key.buf, remote);
+	if (git_config_set_gently(key.buf, remote) < 0)
+		goto out_err;
 
 	if (rebasing) {
 		strbuf_reset(&key);
 		strbuf_addf(&key, "branch.%s.rebase", local);
-		git_config_set(key.buf, "true");
+		if (git_config_set_gently(key.buf, "true") < 0)
+			goto out_err;
 	}
 	strbuf_release(&key);
 
 	if (flag & BRANCH_CONFIG_VERBOSE) {
 		if (shortname) {
 			if (origin)
