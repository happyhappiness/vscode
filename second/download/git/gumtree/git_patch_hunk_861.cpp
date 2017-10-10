 
 	strbuf_addf(&logmsg, "Branch: renamed %s to %s",
 		 oldref.buf, newref.buf);
 
 	if (rename_ref(oldref.buf, newref.buf, logmsg.buf))
 		die(_("Branch rename failed"));
-	strbuf_release(&logmsg);
 
 	if (recovery)
 		warning(_("Renamed a misnamed branch '%s' away"), oldref.buf + 11);
 
-	if (replace_each_worktree_head_symref(oldref.buf, newref.buf))
+	if (replace_each_worktree_head_symref(oldref.buf, newref.buf, logmsg.buf))
 		die(_("Branch renamed to %s, but HEAD is not updated!"), newname);
 
+	strbuf_release(&logmsg);
+
 	strbuf_addf(&oldsection, "branch.%s", oldref.buf + 11);
 	strbuf_release(&oldref);
 	strbuf_addf(&newsection, "branch.%s", newref.buf + 11);
 	strbuf_release(&newref);
 	if (git_config_rename_section(oldsection.buf, newsection.buf) < 0)
 		die(_("Branch is renamed, but update of config-file failed"));
 	strbuf_release(&oldsection);
 	strbuf_release(&newsection);
 }
 
-static const char edit_description[] = "BRANCH_DESCRIPTION";
+static GIT_PATH_FUNC(edit_description, "EDIT_DESCRIPTION")
 
 static int edit_branch_description(const char *branch_name)
 {
 	struct strbuf buf = STRBUF_INIT;
 	struct strbuf name = STRBUF_INIT;
 
