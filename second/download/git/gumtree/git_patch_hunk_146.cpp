 		return git_config_string(&pager_program, var, value);
 
 	if (!strcmp(var, "core.editor"))
 		return git_config_string(&editor_program, var, value);
 
 	if (!strcmp(var, "core.commentchar")) {
-		const char *comment;
-		int ret = git_config_string(&comment, var, value);
-		if (!ret)
-			comment_line_char = comment[0];
-		return ret;
+		if (!value)
+			return config_error_nonbool(var);
+		else if (!strcasecmp(value, "auto"))
+			auto_comment_line_char = 1;
+		else if (value[0] && !value[1]) {
+			comment_line_char = value[0];
+			auto_comment_line_char = 0;
+		} else
+			return error("core.commentChar should only be one character");
+		return 0;
 	}
 
 	if (!strcmp(var, "core.askpass"))
 		return git_config_string(&askpass_program, var, value);
 
 	if (!strcmp(var, "core.excludesfile"))
