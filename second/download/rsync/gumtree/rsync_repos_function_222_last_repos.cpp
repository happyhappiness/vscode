void write_batch_shell_file(int argc, char *argv[], int file_arg_cnt)
{
	int fd, i, len, err = 0;
	char *p, filename[MAXPATHLEN];

	stringjoin(filename, sizeof filename,
		   batch_name, ".sh", NULL);
	fd = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		     S_IRUSR | S_IWUSR | S_IXUSR);
	if (fd < 0) {
		rsyserr(FERROR, errno, "Batch file %s open error",
			filename);
		exit_cleanup(RERR_FILESELECT);
	}

	/* Write argvs info to BATCH.sh file */
	if (write_arg(fd, argv[0]) < 0)
		err = 1;
	if (filter_list.head) {
		if (protocol_version >= 29)
			write_sbuf(fd, " --filter=._-");
		else
			write_sbuf(fd, " --exclude-from=-");
	}
	for (i = 1; i < argc - file_arg_cnt; i++) {
		p = argv[i];
		if (strncmp(p, "--files-from", 12) == 0
		    || strncmp(p, "--filter", 8) == 0
		    || strncmp(p, "--include", 9) == 0
		    || strncmp(p, "--exclude", 9) == 0) {
			if (strchr(p, '=') == NULL)
				i++;
			continue;
		}
		if (strcmp(p, "-f") == 0) {
			i++;
			continue;
		}
		if (write(fd, " ", 1) != 1)
			err = 1;
		if (strncmp(p, "--write-batch", len = 13) == 0
		 || strncmp(p, "--only-write-batch", len = 18) == 0) {
			if (write(fd, "--read-batch", 12) != 12)
				err = 1;
			if (p[len] == '=') {
				if (write(fd, "=", 1) != 1
				 || write_arg(fd, p + len + 1) < 0)
					err = 1;
			}
		} else {
			if (write_arg(fd, p) < 0)
				err = 1;
		}
	}
	if (!(p = check_for_hostspec(argv[argc - 1], &p, &i)))
		p = argv[argc - 1];
	if (write(fd, " ${1:-", 6) != 6
	 || write_arg(fd, p) < 0)
		err = 1;
	write_byte(fd, '}');
	if (filter_list.head)
		write_filter_rules(fd);
	if (write(fd, "\n", 1) != 1 || close(fd) < 0 || err) {
		rsyserr(FERROR, errno, "Batch file %s write error",
			filename);
		exit_cleanup(RERR_FILEIO);
	}
}