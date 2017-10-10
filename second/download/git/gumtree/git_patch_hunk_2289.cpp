 		putchar('\n');
 		pretty_print_cmdnames(other_cmds, colopts);
 		putchar('\n');
 	}
 }
 
+static int cmd_group_cmp(const void *elem1, const void *elem2)
+{
+	const struct cmdname_help *e1 = elem1;
+	const struct cmdname_help *e2 = elem2;
+
+	if (e1->group < e2->group)
+		return -1;
+	if (e1->group > e2->group)
+		return 1;
+	return strcmp(e1->name, e2->name);
+}
+
 void list_common_cmds_help(void)
 {
 	int i, longest = 0;
+	int current_grp = -1;
 
 	for (i = 0; i < ARRAY_SIZE(common_cmds); i++) {
 		if (longest < strlen(common_cmds[i].name))
 			longest = strlen(common_cmds[i].name);
 	}
 
-	puts(_("The most commonly used git commands are:"));
+	qsort(common_cmds, ARRAY_SIZE(common_cmds),
+		sizeof(common_cmds[0]), cmd_group_cmp);
+
+	puts(_("These are common Git commands used in various situations:"));
+
 	for (i = 0; i < ARRAY_SIZE(common_cmds); i++) {
+		if (common_cmds[i].group != current_grp) {
+			printf("\n%s\n", _(common_cmd_groups[common_cmds[i].group]));
+			current_grp = common_cmds[i].group;
+		}
+
 		printf("   %s   ", common_cmds[i].name);
 		mput_char(' ', longest - strlen(common_cmds[i].name));
 		puts(_(common_cmds[i].help));
 	}
 }
 
