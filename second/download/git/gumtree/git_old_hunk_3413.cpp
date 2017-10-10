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
