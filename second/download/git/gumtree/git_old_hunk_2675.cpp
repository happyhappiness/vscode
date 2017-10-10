		free(private);
	}
	strbuf_release(&buf);
	return ret;
}

static int push_refs_with_push(struct transport *transport,
			       struct ref *remote_refs, int flags)
{
	int force_all = flags & TRANSPORT_PUSH_FORCE;
	int mirror = flags & TRANSPORT_PUSH_MIRROR;
	struct helper_data *data = transport->data;
