	if (fp == NULL) {
		logerror("fdopen of error channel failed");
		close(fd);
		return;
	}

	while (strbuf_getline(&line, fp, '\n') != EOF) {
		logerror("%s", line.buf);
		strbuf_setlen(&line, 0);
	}

	strbuf_release(&line);
	fclose(fp);
