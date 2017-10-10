			s_hdr_data[i] = NULL;
		}
		return 0;
	}

	if (patchbreak(line)) {
		fclose(cmitmsg);
		cmitmsg = NULL;
		return 1;
	}

	fputs(line->buf, cmitmsg);
