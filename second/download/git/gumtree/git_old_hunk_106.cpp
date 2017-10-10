		if (verbosity >= 0 && !merge_msg.len)
			printf(_("No merge message -- not updating HEAD\n"));
		else {
			const char *argv_gc_auto[] = { "gc", "--auto", NULL };
			update_ref(reflog_message.buf, "HEAD",
				new_head, head, 0,
				DIE_ON_ERR);
			/*
			 * We ignore errors in 'gc --auto', since the
			 * user should see them.
			 */
			run_command_v_opt(argv_gc_auto, RUN_GIT_CMD);
		}
