printf("commit %s\nmark :%"PRIu32"\n%.*s\n%.*s\ndata %u\n%s",
	       (const char *)commit->util, last_idnum,
	       (int)(author_end - author), author,
	       (int)(committer_end - committer), committer,
	       (unsigned)(reencoded
			  ? strlen(reencoded) : message
			  ? strlen(message) : 0),
	       reencoded ? reencoded : message ? message : "");