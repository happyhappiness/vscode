 	if (argc > 3)
 		oldurl = argv[3];
 
 	if (delete_mode)
 		oldurl = newurl;
 
-	if (!remote_is_configured(remotename))
-		die(_("No such remote '%s'"), remotename);
 	remote = remote_get(remotename);
+	if (!remote_is_configured(remote))
+		die(_("No such remote '%s'"), remotename);
 
 	if (push_mode) {
 		strbuf_addf(&name_buf, "remote.%s.pushurl", remotename);
 		urlset = remote->pushurl;
 		urlset_nr = remote->pushurl_nr;
 	} else {
