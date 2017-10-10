		goto fail;
	}

	/* flush the data */
	if (0 <= buffered) {
		data[0] = buffered;
		send_client_data(1, data, 1);
		fprintf(stderr, "flushed.\n");
	}
	if (use_sideband)
		packet_flush(1);
	return;

