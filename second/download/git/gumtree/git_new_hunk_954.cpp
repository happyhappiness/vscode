	}
	if (run_update_hook(cmd)) {
		rp_error("hook declined to update %s", name);
		return "hook declined";
	}

	if (is_null_oid(new_oid)) {
		struct strbuf err = STRBUF_INIT;
		if (!parse_object(old_oid->hash)) {
			old_oid = NULL;
			if (ref_exists(name)) {
				rp_warning("Allowing deletion of corrupt ref.");
			} else {
				rp_warning("Deleting a non-existent ref.");
				cmd->did_not_exist = 1;
			}
		}
		if (ref_transaction_delete(transaction,
					   namespaced_name,
					   old_oid->hash,
					   0, "push", &err)) {
			rp_error("%s", err.buf);
			strbuf_release(&err);
			return "failed to delete";
		}
		strbuf_release(&err);
