			else if (cmd->out)
				close(cmd->out);
			str = "standard error";
fail_pipe:
			error("cannot create %s pipe for %s: %s",
				str, cmd->argv[0], strerror(failed_errno));
			argv_array_clear(&cmd->args);
			argv_array_clear(&cmd->env_array);
			errno = failed_errno;
			return -1;
		}
		cmd->err = fderr[0];
	}

