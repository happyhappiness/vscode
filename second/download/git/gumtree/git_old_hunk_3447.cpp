		child_process_init(&pp->children[i].process);

		if (i != pp->output_owner) {
			strbuf_addbuf(&pp->buffered_output, &pp->children[i].err);
			strbuf_reset(&pp->children[i].err);
		} else {
			fputs(pp->children[i].err.buf, stderr);
			strbuf_reset(&pp->children[i].err);

			/* Output all other finished child processes */
			fputs(pp->buffered_output.buf, stderr);
			strbuf_reset(&pp->buffered_output);

			/*
			 * Pick next process to output live.
			 * NEEDSWORK:
			 * For now we pick it randomly by doing a round
