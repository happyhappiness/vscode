	if (run_update_hook(cmd)) {
		rp_error("hook declined to update %s", name);
		return "hook declined";
	}

	if (is_null_sha1(new_sha1)) {
		struct strbuf err = STRBUF_INIT;
		if (!parse_object(old_sha1)) {
			old_sha1 = NULL;
			if (ref_exists(name)) {
				rp_warning("Allowing deletion of corrupt ref.");
			} else {
				rp_warning("Deleting a non-existent ref.");
				cmd->did_not_exist = 1;
			}
		}
		if (ref_transaction_delete(transaction,
					   namespaced_name,
					   old_sha1,
					   0, "push", &err)) {
			rp_error("%s", err.buf);
			strbuf_release(&err);
			return "failed to delete";
		}
		strbuf_release(&err);
		return NULL; /* good */
	}
	else {
		struct strbuf err = STRBUF_INIT;
		if (shallow_update && si->shallow_ref[cmd->index] &&
		    update_shallow_ref(cmd, si))
			return "shallow error";

		if (ref_transaction_update(transaction,
					   namespaced_name,
					   new_sha1, old_sha1,
					   0, "push",
					   &err)) {
			rp_error("%s", err.buf);
			strbuf_release(&err);

			return "failed to update ref";
		}
		strbuf_release(&err);

		return NULL; /* good */
	}
}

static void run_update_post_hook(struct command *commands)
{
