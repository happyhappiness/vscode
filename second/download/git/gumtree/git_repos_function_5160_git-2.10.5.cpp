static void execute_commands_non_atomic(struct command *commands,
					struct shallow_info *si)
{
	struct command *cmd;
	struct strbuf err = STRBUF_INIT;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!should_process_cmd(cmd))
			continue;

		transaction = ref_transaction_begin(&err);
		if (!transaction) {
			rp_error("%s", err.buf);
			strbuf_reset(&err);
			cmd->error_string = "transaction failed to start";
			continue;
		}

		cmd->error_string = update(cmd, si);

		if (!cmd->error_string
		    && ref_transaction_commit(transaction, &err)) {
			rp_error("%s", err.buf);
			strbuf_reset(&err);
			cmd->error_string = "failed to update ref";
		}
		ref_transaction_free(transaction);
	}
	strbuf_release(&err);
}