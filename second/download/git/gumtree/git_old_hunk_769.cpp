		}
	}

	return enabled ? &allowed : NULL;
}

int is_transport_allowed(const char *type)
{
	const struct string_list *allowed = protocol_whitelist();
	return !allowed || string_list_has_string(allowed, type);
}

void transport_check_allowed(const char *type)
{
	if (!is_transport_allowed(type))
		die("transport '%s' not allowed", type);
}

int transport_restrict_protocols(void)
{
	return !!protocol_whitelist();
}

struct transport *transport_get(struct remote *remote, const char *url)
{
	const char *helper;
	struct transport *ret = xcalloc(1, sizeof(*ret));

	ret->progress = isatty(2);
