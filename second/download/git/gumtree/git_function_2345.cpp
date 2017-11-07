struct http_object_request *new_http_object_request(const char *base_url,
	unsigned char *sha1)
{
	char *hex = sha1_to_hex(sha1);
	const char *filename;
	char prevfile[PATH_MAX];
	int prevlocal;
	char prev_buf[PREV_BUF_SIZE];
	ssize_t prev_read = 0;
	off_t prev_posn = 0;
	struct http_object_request *freq;

	freq = xcalloc(1, sizeof(*freq));
	hashcpy(freq->sha1, sha1);
	freq->localfile = -1;

	filename = sha1_file_name(sha1);
	snprintf(freq->tmpfile, sizeof(freq->tmpfile),
		 "%s.temp", filename);

	snprintf(prevfile, sizeof(prevfile), "%s.prev", filename);
	unlink_or_warn(prevfile);
	rename(freq->tmpfile, prevfile);
	unlink_or_warn(freq->tmpfile);

	if (freq->localfile != -1)
		error("fd leakage in start: %d", freq->localfile);
	freq->localfile = open(freq->tmpfile,
			       O_WRONLY | O_CREAT | O_EXCL, 0666);
	/*
	 * This could have failed due to the "lazy directory creation";
	 * try to mkdir the last path component.
	 */
	if (freq->localfile < 0 && errno == ENOENT) {
		char *dir = strrchr(freq->tmpfile, '/');
		if (dir) {
			*dir = 0;
			mkdir(freq->tmpfile, 0777);
			*dir = '/';
		}
		freq->localfile = open(freq->tmpfile,
				       O_WRONLY | O_CREAT | O_EXCL, 0666);
	}

	if (freq->localfile < 0) {
		error("Couldn't create temporary file %s: %s",
		      freq->tmpfile, strerror(errno));
		goto abort;
	}

	git_inflate_init(&freq->stream);

	git_SHA1_Init(&freq->c);

	freq->url = get_remote_object_url(base_url, hex, 0);

	/*
	 * If a previous temp file is present, process what was already
	 * fetched.
	 */
	prevlocal = open(prevfile, O_RDONLY);
	if (prevlocal != -1) {
		do {
			prev_read = xread(prevlocal, prev_buf, PREV_BUF_SIZE);
			if (prev_read>0) {
				if (fwrite_sha1_file(prev_buf,
						     1,
						     prev_read,
						     freq) == prev_read) {
					prev_posn += prev_read;
				} else {
					prev_read = -1;
				}
			}
		} while (prev_read > 0);
		close(prevlocal);
	}
	unlink_or_warn(prevfile);

	/*
	 * Reset inflate/SHA1 if there was an error reading the previous temp
	 * file; also rewind to the beginning of the local file.
	 */
	if (prev_read == -1) {
		memset(&freq->stream, 0, sizeof(freq->stream));
		git_inflate_init(&freq->stream);
		git_SHA1_Init(&freq->c);
		if (prev_posn>0) {
			prev_posn = 0;
			lseek(freq->localfile, 0, SEEK_SET);
			if (ftruncate(freq->localfile, 0) < 0) {
				error("Couldn't truncate temporary file %s: %s",
					  freq->tmpfile, strerror(errno));
				goto abort;
			}
		}
	}

	freq->slot = get_active_slot();

	curl_easy_setopt(freq->slot->curl, CURLOPT_FILE, freq);
	curl_easy_setopt(freq->slot->curl, CURLOPT_WRITEFUNCTION, fwrite_sha1_file);
	curl_easy_setopt(freq->slot->curl, CURLOPT_ERRORBUFFER, freq->errorstr);
	curl_easy_setopt(freq->slot->curl, CURLOPT_URL, freq->url);
	curl_easy_setopt(freq->slot->curl, CURLOPT_HTTPHEADER, no_pragma_header);

	/*
	 * If we have successfully processed data from a previous fetch
	 * attempt, only fetch the data we don't already have.
	 */
	if (prev_posn>0) {
		if (http_is_verbose)
			fprintf(stderr,
				"Resuming fetch of object %s at byte %"PRIuMAX"\n",
				hex, (uintmax_t)prev_posn);
		http_opt_request_remainder(freq->slot->curl, prev_posn);
	}

	return freq;

abort:
	free(freq->url);
	free(freq);
	return NULL;
}