				 url, revision, uuid);
	} else {
		*gitsvnline = '\0';
	}
	printf("commit %s\n", local_ref);
	printf("mark :%"PRIu32"\n", revision);
	printf("committer %s <%s@%s> %lu +0000\n",
		   *author ? author : "nobody",
		   *author ? author : "nobody",
		   *uuid ? uuid : "local", timestamp);
	printf("data %"PRIuMAX"\n",
		(uintmax_t) (log->len + strlen(gitsvnline)));
	fwrite(log->buf, log->len, 1, stdout);
