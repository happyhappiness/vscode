 	res = xcalloc(1, sizeof(*res));
 	while ((line = *(list++)) != NULL)
 		handle_attr_line(res, line, "[builtin]", ++lineno, 1);
 	return res;
 }
 
+/*
+ * Callers into the attribute system assume there is a single, system-wide
+ * global state where attributes are read from and when the state is flipped by
+ * calling git_attr_set_direction(), the stack frames that have been
+ * constructed need to be discarded so so that subsequent calls into the
+ * attribute system will lazily read from the right place.  Since changing
+ * direction causes a global paradigm shift, it should not ever be called while
+ * another thread could potentially be calling into the attribute system.
+ */
 static enum git_attr_direction direction;
 static struct index_state *use_index;
 
+void git_attr_set_direction(enum git_attr_direction new_direction,
+			    struct index_state *istate)
+{
+	if (is_bare_repository() && new_direction != GIT_ATTR_INDEX)
+		die("BUG: non-INDEX attr direction in a bare repo");
+
+	if (new_direction != direction)
+		drop_all_attr_stacks();
+
+	direction = new_direction;
+	use_index = istate;
+}
+
 static struct attr_stack *read_attr_from_file(const char *path, int macro_ok)
 {
 	FILE *fp = fopen(path, "r");
 	struct attr_stack *res;
 	char buf[2048];
 	int lineno = 0;
