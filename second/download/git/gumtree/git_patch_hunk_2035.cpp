 }
 
 static void exec_man_cmd(const char *cmd, const char *page)
 {
 	struct strbuf shell_cmd = STRBUF_INIT;
 	strbuf_addf(&shell_cmd, "%s %s", cmd, page);
-	execl("/bin/sh", "sh", "-c", shell_cmd.buf, (char *)NULL);
+	execl(SHELL_PATH, SHELL_PATH, "-c", shell_cmd.buf, (char *)NULL);
 	warning(_("failed to exec '%s': %s"), cmd, strerror(errno));
 }
 
 static void add_man_viewer(const char *name)
 {
 	struct man_viewer_list **p = &man_viewer_list;
