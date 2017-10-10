 			else if (valid == TODO_PICK)
 				return error(_("cannot cherry-pick during a revert."));
 			else
 				return error(_("cannot revert during a cherry-pick."));
 	}
 
+	if (is_rebase_i(opts)) {
+		struct todo_list done = TODO_LIST_INIT;
+		FILE *f = fopen(rebase_path_msgtotal(), "w");
+
+		if (strbuf_read_file(&done.buf, rebase_path_done(), 0) > 0 &&
+				!parse_insn_buffer(done.buf.buf, &done))
+			todo_list->done_nr = count_commands(&done);
+		else
+			todo_list->done_nr = 0;
+
+		todo_list->total_nr = todo_list->done_nr
+			+ count_commands(todo_list);
+		todo_list_release(&done);
+
+		if (f) {
+			fprintf(f, "%d\n", todo_list->total_nr);
+			fclose(f);
+		}
+	}
+
 	return 0;
 }
 
 static int git_config_string_dup(char **dest,
 				 const char *var, const char *value)
 {
