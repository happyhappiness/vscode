		}
		freq->localfile = open(freq->tmpfile,
				       O_WRONLY | O_CREAT | O_EXCL, 0666);
	}

	if (freq->localfile < 0) {
		error_errno("Couldn't create temporary file %s", freq->tmpfile);
		goto abort;
	}

	git_inflate_init(&freq->stream);

	git_SHA1_Init(&freq->c);
