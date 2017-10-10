	} else if (data->import || data->bidi_import || data->export) {
		warning("This remote helper should implement refspec capability.");
	}
	strbuf_release(&buf);
	if (debug)
		fprintf(stderr, "Debug: Capabilities complete.\n");
	standard_options(transport);
	return data->helper;
}

static int disconnect_helper(struct transport *transport)
{
	struct helper_data *data = transport->data;
