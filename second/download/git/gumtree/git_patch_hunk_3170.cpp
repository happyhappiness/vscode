 
 	rename.old = argv[1];
 	rename.new = argv[2];
 	rename.remote_branches = &remote_branches;
 
 	oldremote = remote_get(rename.old);
-	if (!oldremote)
+	if (!remote_is_configured(oldremote))
 		die(_("No such remote: %s"), rename.old);
 
 	if (!strcmp(rename.old, rename.new) && oldremote->origin != REMOTE_CONFIG)
 		return migrate_file(oldremote);
 
 	newremote = remote_get(rename.new);
-	if (newremote && (newremote->url_nr > 1 || newremote->fetch_refspec_nr))
+	if (remote_is_configured(newremote))
 		die(_("remote %s already exists."), rename.new);
 
 	strbuf_addf(&buf, "refs/heads/test:refs/remotes/%s/test", rename.new);
 	if (!valid_fetch_refspec(buf.buf))
 		die(_("'%s' is not a valid remote name"), rename.new);
 
