 		cmd->argv = prepare_shell_cmd(&nargv, cmd->argv);
 
 	cmd->pid = mingw_spawnvpe(cmd->argv[0], cmd->argv, (char**) cmd->env,
 			cmd->dir, fhin, fhout, fherr);
 	failed_errno = errno;
 	if (cmd->pid < 0 && (!cmd->silent_exec_failure || errno != ENOENT))
-		error("cannot spawn %s: %s", cmd->argv[0], strerror(errno));
+		error_errno("cannot spawn %s", cmd->argv[0]);
 	if (cmd->clean_on_exit && cmd->pid >= 0)
 		mark_child_for_cleanup(cmd->pid);
 
 	argv_array_clear(&nargv);
 	cmd->argv = sargv;
 	if (fhin != 0)
