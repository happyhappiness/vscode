 		strbuf_addch(&sb, '\n');
 		fprintf(f, "%s", sb.buf);
 	}
 	strbuf_release(&sb);
 }
 
+static void prepare_submodule_repo_env_no_git_dir(struct argv_array *out)
+{
+	const char * const *var;
+
+	for (var = local_repo_env; *var; var++) {
+		if (strcmp(*var, CONFIG_DATA_ENVIRONMENT))
+			argv_array_push(out, *var);
+	}
+}
+
+void prepare_submodule_repo_env(struct argv_array *out)
+{
+	prepare_submodule_repo_env_no_git_dir(out);
+	argv_array_pushf(out, "%s=%s", GIT_DIR_ENVIRONMENT,
+			 DEFAULT_GIT_DIR_ENVIRONMENT);
+}
+
 /* Helper function to display the submodule header line prior to the full
  * summary output. If it can locate the submodule objects directory it will
  * attempt to lookup both the left and right commits and put them into the
  * left and right pointers.
  */
 static void show_submodule_header(FILE *f, const char *path,
