			_("Please supply the message using either -m or -F option.\n"));
			exit(1);
		}
	}

	if (opt->cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(buf, opt->cleanup_mode == CLEANUP_ALL);

	if (!opt->message_given && !buf->len)
		die(_("no tag message?"));

	strbuf_insert(buf, 0, header_buf, header_len);

