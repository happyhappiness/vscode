					  len - strlen("encoding \n"),
					  encoding, strlen(encoding));
	}
	return strbuf_detach(&tmp, NULL);
}

const char *logmsg_reencode(const struct commit *commit,
			    char **commit_encoding,
			    const char *output_encoding)
{
	static const char *utf8 = "UTF-8";
	const char *use_encoding;
	char *encoding;
	const char *msg = get_commit_buffer(commit, NULL);
	char *out;

	if (!output_encoding || !*output_encoding) {
		if (commit_encoding)
			*commit_encoding =
				get_header(commit, msg, "encoding");
		return msg;
	}
