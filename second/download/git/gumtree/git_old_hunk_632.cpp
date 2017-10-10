		die("Authentication failed for '%s'", url.buf);
	default:
		show_http_message(&type, &charset, &buffer);
		die("unable to access '%s': %s", url.buf, curl_errorstr);
	}

	last= xcalloc(1, sizeof(*last_discovery));
	last->service = service;
	last->buf_alloc = strbuf_detach(&buffer, &last->len);
	last->buf = last->buf_alloc;

	strbuf_addf(&exp, "application/x-%s-advertisement", service);
