		setup_iconv();
#endif
		if (protect_args && !daemon_over_rsh)
			send_protected_args(*f_out_p, args);
	}

	if (need_to_free)
		free(need_to_free);

	return pid;

  oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
}
