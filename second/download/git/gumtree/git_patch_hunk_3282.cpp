 		warning(_("templates not found %s"), template_dir);
 		goto free_return;
 	}
 
 	/* Make sure that template is from the correct vintage */
 	strbuf_addstr(&template_path, "config");
-	repository_format_version = 0;
-	git_config_from_file(check_repository_format_version,
-			     template_path.buf, NULL);
+	read_repository_format(&template_format, template_path.buf);
 	strbuf_setlen(&template_path, template_len);
 
-	if (repository_format_version &&
-	    repository_format_version != GIT_REPO_VERSION) {
-		warning(_("not copying templates of "
-			"a wrong format version %d from '%s'"),
-			repository_format_version,
-			template_dir);
+	/*
+	 * No mention of version at all is OK, but anything else should be
+	 * verified.
+	 */
+	if (template_format.version >= 0 &&
+	    verify_repository_format(&template_format, &err) < 0) {
+		warning(_("not copying templates from '%s': %s"),
+			  template_dir, err.buf);
+		strbuf_release(&err);
 		goto close_free_return;
 	}
 
 	strbuf_addstr(&path, get_git_dir());
 	strbuf_complete(&path, '/');
 	copy_templates_1(&path, &template_path, dir);
