 	prepare_submodule_repo_env(&cp.env_array);
 	cp.no_stdin = 1;
 
 	return run_command(&cp);
 }
 
+struct submodule_alternate_setup {
+	const char *submodule_name;
+	enum SUBMODULE_ALTERNATE_ERROR_MODE {
+		SUBMODULE_ALTERNATE_ERROR_DIE,
+		SUBMODULE_ALTERNATE_ERROR_INFO,
+		SUBMODULE_ALTERNATE_ERROR_IGNORE
+	} error_mode;
+	struct string_list *reference;
+};
+#define SUBMODULE_ALTERNATE_SETUP_INIT { NULL, \
+	SUBMODULE_ALTERNATE_ERROR_IGNORE, NULL }
+
+static int add_possible_reference_from_superproject(
+		struct alternate_object_database *alt, void *sas_cb)
+{
+	struct submodule_alternate_setup *sas = sas_cb;
+
+	/*
+	 * If the alternate object store is another repository, try the
+	 * standard layout with .git/modules/<name>/objects
+	 */
+	if (ends_with(alt->path, ".git/objects")) {
+		char *sm_alternate;
+		struct strbuf sb = STRBUF_INIT;
+		struct strbuf err = STRBUF_INIT;
+		strbuf_add(&sb, alt->path, strlen(alt->path) - strlen("objects"));
+
+		/*
+		 * We need to end the new path with '/' to mark it as a dir,
+		 * otherwise a submodule name containing '/' will be broken
+		 * as the last part of a missing submodule reference would
+		 * be taken as a file name.
+		 */
+		strbuf_addf(&sb, "modules/%s/", sas->submodule_name);
+
+		sm_alternate = compute_alternate_path(sb.buf, &err);
+		if (sm_alternate) {
+			string_list_append(sas->reference, xstrdup(sb.buf));
+			free(sm_alternate);
+		} else {
+			switch (sas->error_mode) {
+			case SUBMODULE_ALTERNATE_ERROR_DIE:
+				die(_("submodule '%s' cannot add alternate: %s"),
+				    sas->submodule_name, err.buf);
+			case SUBMODULE_ALTERNATE_ERROR_INFO:
+				fprintf(stderr, _("submodule '%s' cannot add alternate: %s"),
+					sas->submodule_name, err.buf);
+			case SUBMODULE_ALTERNATE_ERROR_IGNORE:
+				; /* nothing */
+			}
+		}
+		strbuf_release(&sb);
+	}
+
+	return 0;
+}
+
+static void prepare_possible_alternates(const char *sm_name,
+		struct string_list *reference)
+{
+	char *sm_alternate = NULL, *error_strategy = NULL;
+	struct submodule_alternate_setup sas = SUBMODULE_ALTERNATE_SETUP_INIT;
+
+	git_config_get_string("submodule.alternateLocation", &sm_alternate);
+	if (!sm_alternate)
+		return;
+
+	git_config_get_string("submodule.alternateErrorStrategy", &error_strategy);
+
+	if (!error_strategy)
+		error_strategy = xstrdup("die");
+
+	sas.submodule_name = sm_name;
+	sas.reference = reference;
+	if (!strcmp(error_strategy, "die"))
+		sas.error_mode = SUBMODULE_ALTERNATE_ERROR_DIE;
+	else if (!strcmp(error_strategy, "info"))
+		sas.error_mode = SUBMODULE_ALTERNATE_ERROR_INFO;
+	else if (!strcmp(error_strategy, "ignore"))
+		sas.error_mode = SUBMODULE_ALTERNATE_ERROR_IGNORE;
+	else
+		die(_("Value '%s' for submodule.alternateErrorStrategy is not recognized"), error_strategy);
+
+	if (!strcmp(sm_alternate, "superproject"))
+		foreach_alt_odb(add_possible_reference_from_superproject, &sas);
+	else if (!strcmp(sm_alternate, "no"))
+		; /* do nothing */
+	else
+		die(_("Value '%s' for submodule.alternateLocation is not recognized"), sm_alternate);
+
+	free(sm_alternate);
+	free(error_strategy);
+}
+
 static int module_clone(int argc, const char **argv, const char *prefix)
 {
-	const char *name = NULL, *url = NULL;
-	const char *reference = NULL, *depth = NULL;
+	const char *name = NULL, *url = NULL, *depth = NULL;
 	int quiet = 0;
+	int progress = 0;
 	FILE *submodule_dot_git;
 	char *p, *path = NULL, *sm_gitdir;
 	struct strbuf rel_path = STRBUF_INIT;
 	struct strbuf sb = STRBUF_INIT;
+	struct string_list reference = STRING_LIST_INIT_NODUP;
 
 	struct option module_clone_options[] = {
 		OPT_STRING(0, "prefix", &prefix,
 			   N_("path"),
 			   N_("alternative anchor for relative paths")),
 		OPT_STRING(0, "path", &path,
