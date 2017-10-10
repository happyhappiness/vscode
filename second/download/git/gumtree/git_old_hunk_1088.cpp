				return res | error_with_patch(item->commit,
					item->arg, item->arg_len, opts, res,
					item->command == TODO_REWORD);
		} else if (item->command == TODO_EXEC) {
			char *end_of_arg = (char *)(item->arg + item->arg_len);
			int saved = *end_of_arg;

			*end_of_arg = '\0';
			res = do_exec(item->arg);
			*end_of_arg = saved;
		} else if (!is_noop(item->command))
			return error(_("unknown command %d"), item->command);

		todo_list->current++;
		if (res)
			return res;
