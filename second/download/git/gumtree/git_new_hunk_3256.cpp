			printf("Would set upstream of '%s' to '%s' of '%s'\n",
				localname + 11, remotename + 11,
				transport->remote->name);
	}
}

struct bundle_transport_data {
	int fd;
	struct bundle_header header;
};

static struct ref *get_refs_from_bundle(struct transport *transport, int for_push)
