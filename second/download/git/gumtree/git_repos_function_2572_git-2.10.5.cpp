static void serve_one_client(FILE *in, FILE *out)
{
	struct credential c = CREDENTIAL_INIT;
	struct strbuf action = STRBUF_INIT;
	int timeout = -1;

	if (read_request(in, &c, &action, &timeout) < 0)
		/* ignore error */ ;
	else if (!strcmp(action.buf, "get")) {
		struct credential_cache_entry *e = lookup_credential(&c);
		if (e) {
			fprintf(out, "username=%s\n", e->item.username);
			fprintf(out, "password=%s\n", e->item.password);
		}
	}
	else if (!strcmp(action.buf, "exit")) {
		/*
		 * It's important that we clean up our socket first, and then
		 * signal the client only once we have finished the cleanup.
		 * Calling exit() directly does this, because we clean up in
		 * our atexit() handler, and then signal the client when our
		 * process actually ends, which closes the socket and gives
		 * them EOF.
		 */
		exit(0);
	}
	else if (!strcmp(action.buf, "erase"))
		remove_credential(&c);
	else if (!strcmp(action.buf, "store")) {
		if (timeout < 0)
			warning("cache client didn't specify a timeout");
		else if (!c.username || !c.password)
			warning("cache client gave us a partial credential");
		else {
			remove_credential(&c);
			cache_credential(&c, timeout);
		}
	}
	else
		warning("cache client sent unknown action: %s", action.buf);

	credential_clear(&c);
	strbuf_release(&action);
}