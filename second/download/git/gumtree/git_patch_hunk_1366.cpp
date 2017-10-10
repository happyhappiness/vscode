 	{"is-active", is_active, 0},
 };
 
 int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
 {
 	int i;
-	if (argc < 2)
-		die(_("submodule--helper subcommand must be "
-		      "called with a subcommand"));
+	if (argc < 2 || !strcmp(argv[1], "-h"))
+		usage("git submodule--helper <command>");
 
 	for (i = 0; i < ARRAY_SIZE(commands); i++) {
 		if (!strcmp(argv[1], commands[i].cmd)) {
 			if (get_super_prefix() &&
 			    !(commands[i].option & SUPPORT_SUPER_PREFIX))
 				die(_("%s doesn't support --super-prefix"),
