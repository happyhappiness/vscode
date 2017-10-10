 {
 	return gitdiff_verify_name(state, line,
 				   patch->is_delete, &patch->new_name,
 				   DIFF_NEW_NAME);
 }
 
+static int parse_mode_line(const char *line, int linenr, unsigned int *mode)
+{
+	char *end;
+	*mode = strtoul(line, &end, 8);
+	if (end == line || !isspace(*end))
+		return error(_("invalid mode on line %d: %s"), linenr, line);
+	return 0;
+}
+
 static int gitdiff_oldmode(struct apply_state *state,
 			   const char *line,
 			   struct patch *patch)
 {
-	patch->old_mode = strtoul(line, NULL, 8);
-	return 0;
+	return parse_mode_line(line, state->linenr, &patch->old_mode);
 }
 
 static int gitdiff_newmode(struct apply_state *state,
 			   const char *line,
 			   struct patch *patch)
 {
-	patch->new_mode = strtoul(line, NULL, 8);
-	return 0;
+	return parse_mode_line(line, state->linenr, &patch->new_mode);
 }
 
 static int gitdiff_delete(struct apply_state *state,
 			  const char *line,
 			  struct patch *patch)
 {
