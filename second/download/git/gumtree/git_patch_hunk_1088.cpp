 				return res | error_with_patch(item->commit,
 					item->arg, item->arg_len, opts, res,
 					item->command == TODO_REWORD);
 		} else if (item->command == TODO_EXEC) {
 			char *end_of_arg = (char *)(item->arg + item->arg_len);
 			int saved = *end_of_arg;
+			struct stat st;
 
 			*end_of_arg = '\0';
 			res = do_exec(item->arg);
 			*end_of_arg = saved;
+
+			/* Reread the todo file if it has changed. */
+			if (res)
+				; /* fall through */
+			else if (stat(get_todo_path(opts), &st))
+				res = error_errno(_("could not stat '%s'"),
+						  get_todo_path(opts));
+			else if (match_stat_data(&todo_list->stat, &st)) {
+				todo_list_release(todo_list);
+				if (read_populate_todo(todo_list, opts))
+					res = -1; /* message was printed */
+				/* `current` will be incremented below */
+				todo_list->current = -1;
+			}
 		} else if (!is_noop(item->command))
 			return error(_("unknown command %d"), item->command);
 
 		todo_list->current++;
 		if (res)
 			return res;
