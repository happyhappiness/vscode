		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
			die("helper %s does not support --signed", name);
	} else if (flags & TRANSPORT_PUSH_CERT_IF_ASKED) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "if-asked") != 0)
			die("helper %s does not support --signed=if-asked", name);
	}
}

static int push_refs_with_push(struct transport *transport,
			       struct ref *remote_refs, int flags)
{
	int force_all = flags & TRANSPORT_PUSH_FORCE;
