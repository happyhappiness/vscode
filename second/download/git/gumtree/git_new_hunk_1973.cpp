			s_hdr_data[i] = NULL;
		}
		return 0;
	}

	if (patchbreak(line)) {
		if (message_id)
			fprintf(cmitmsg, "Message-Id: %s\n", message_id);
		fclose(cmitmsg);
		cmitmsg = NULL;
		return 1;
	}

	fputs(line->buf, cmitmsg);
