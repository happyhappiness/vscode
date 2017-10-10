			rp_error("failed to delete %s", name);
			return "failed to delete";
		}
		return NULL; /* good */
	}
	else {
		if (shallow_update && si->shallow_ref[cmd->index] &&
		    update_shallow_ref(cmd, si))
			return "shallow error";

		lock = lock_any_ref_for_update(namespaced_name, old_sha1,
					       0, NULL);
		if (!lock) {
			rp_error("failed to lock %s", name);
			return "failed to lock";
		}
		if (write_ref_sha1(lock, new_sha1, "push")) {
			return "failed to write"; /* error() already called */
		}
		return NULL; /* good */
	}
}

static void run_update_post_hook(struct command *commands)
{
	struct command *cmd;
	int argc;
	const char **argv;
	struct child_process proc;
	char *hook;

	hook = find_hook("post-update");
	for (argc = 0, cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string || cmd->did_not_exist)
			continue;
