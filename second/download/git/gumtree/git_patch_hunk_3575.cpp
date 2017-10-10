 	return mkpath("%s/%s", state->dir, path);
 }
 
 /**
  * For convenience to call write_file()
  */
-static int write_state_text(const struct am_state *state,
-			    const char *name, const char *string)
+static void write_state_text(const struct am_state *state,
+			     const char *name, const char *string)
 {
-	return write_file(am_path(state, name), "%s", string);
+	write_file(am_path(state, name), "%s", string);
 }
 
-static int write_state_count(const struct am_state *state,
-			     const char *name, int value)
+static void write_state_count(const struct am_state *state,
+			      const char *name, int value)
 {
-	return write_file(am_path(state, name), "%d", value);
+	write_file(am_path(state, name), "%d", value);
 }
 
-static int write_state_bool(const struct am_state *state,
-			    const char *name, int value)
+static void write_state_bool(const struct am_state *state,
+			     const char *name, int value)
 {
-	return write_state_text(state, name, value ? "t" : "f");
+	write_state_text(state, name, value ? "t" : "f");
 }
 
 /**
  * If state->quiet is false, calls fprintf(fp, fmt, ...), and appends a newline
  * at the end.
  */
