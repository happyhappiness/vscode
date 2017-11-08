static void log_formatted(enum logcode code,
			  char *format, char *op, struct file_struct *file,
			  struct stats *initial_stats)
{
	extern int module_id;
	extern char *auth_user;
	char buf[1024];
	char buf2[1024];
	char *p, *s, *n;
	size_t l;
	extern struct stats stats;		
	extern int am_sender;
	extern int am_daemon;
	int64 b;

	/* We expand % codes one by one in place in buf.  We don't
	 * copy in the terminating nul of the inserted strings, but
	 * rather keep going until we reach the nul of the format.
	 * Just to make sure we don't clobber that nul and therefore
	 * accidentally keep going, we zero the buffer now. */
	memset(buf, 0, sizeof buf);
	strlcpy(buf, format, sizeof(buf));
	
	for (s=&buf[0]; 
	     s && (p=strchr(s,'%')); ) {
		n = NULL;
		s = p + 1;

		switch (p[1]) {
		case 'h': if (am_daemon) n = client_name(0); break;
		case 'a': if (am_daemon) n = client_addr(0); break;
		case 'l': 
			snprintf(buf2,sizeof(buf2),"%.0f", 
				 (double)file->length); 
			n = buf2;
			break;
		case 'p': 
			snprintf(buf2,sizeof(buf2),"%d", 
				 (int)getpid()); 
			n = buf2;
			break;
		case 'o': n = op; break;
		case 'f': 
			snprintf(buf2, sizeof(buf2), "%s/%s", 
				 file->basedir?file->basedir:"", 
				 f_name(file));
			clean_fname(buf2);
			n = buf2; 
			if (*n == '/') n++;
			break;
		case 'm': n = lp_name(module_id); break;
		case 't': n = timestring(time(NULL)); break;
		case 'P': n = lp_path(module_id); break;
		case 'u': n = auth_user; break;
		case 'b': 
			if (am_sender) {
				b = stats.total_written - 
					initial_stats->total_written;
			} else {
				b = stats.total_read - 
					initial_stats->total_read;
			}
			snprintf(buf2,sizeof(buf2),"%.0f", (double)b); 
			n = buf2;
			break;
		case 'c': 
			if (!am_sender) {
				b = stats.total_written - 
					initial_stats->total_written;
			} else {
				b = stats.total_read - 
					initial_stats->total_read;
			}
			snprintf(buf2,sizeof(buf2),"%.0f", (double)b); 
			n = buf2;
			break;
		}

		/* n is the string to be inserted in place of this %
		 * code; l is its length not including the trailing
		 * NUL */
		if (!n)
			continue;

		l = strlen(n);

		if (l + ((int)(s - &buf[0])) >= sizeof(buf)) {
			rprintf(FERROR,"buffer overflow expanding %%%c - exiting\n",
				p[0]);
			exit_cleanup(RERR_MESSAGEIO);
		}

		/* Shuffle the rest of the string along to make space for n */
		if (l != 2) {
			memmove(s+(l-1), s+1, strlen(s+1)+1);
		}

		/* Copy in n but NOT its nul, because the format sting
		 * probably continues after this. */
		memcpy(p, n, l);

		/* Skip over inserted string; continue looking */
		s = p+l;
	}

	rprintf(code,"%s\n", buf);
}