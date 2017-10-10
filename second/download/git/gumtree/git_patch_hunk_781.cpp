 		int nr_lines_to_show = 2;
 
 		struct string_list have_done = STRING_LIST_INIT_DUP;
 		struct string_list yet_to_do = STRING_LIST_INIT_DUP;
 
 		read_rebase_todolist("rebase-merge/done", &have_done);
-		read_rebase_todolist("rebase-merge/git-rebase-todo", &yet_to_do);
-
+		if (read_rebase_todolist("rebase-merge/git-rebase-todo",
+					 &yet_to_do))
+			status_printf_ln(s, color,
+				_("git-rebase-todo is missing."));
 		if (have_done.nr == 0)
 			status_printf_ln(s, color, _("No commands done."));
 		else {
 			status_printf_ln(s, color,
 				Q_("Last command done (%d command done):",
 					"Last commands done (%d commands done):",
