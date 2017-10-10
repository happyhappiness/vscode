			else if (cmd->out)
				close(cmd->out);
			str = "standard error";
fail_pipe:
			error("cannot create %s pipe for %s: %s",
				str, cmd->argv[0], strerror(failed_errno));
			child_process_clear(cmd);
			errno = failed_errno;
			return -1;
		}
		cmd->err = fderr[0];
	}

