    {
	unsigned len = SCOREBOARD_SIZE;

	m = mmap((caddr_t) 0xC0000000, &len,
		 PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, NOFD, 0);
    }
#elif defined(MAP_TMPFILE)
    {
	char mfile[] = "/tmp/apache_shmem_XXXX";
	int fd = mkstemp(mfile);
	if (fd == -1) {
	    perror("open");
	    fprintf(stderr, "httpd: Could not open %s\n", mfile);
	    exit(APEXIT_INIT);
	}
	m = mmap((caddr_t) 0, SCOREBOARD_SIZE,
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (m == (caddr_t) - 1) {
	    perror("mmap");
	    fprintf(stderr, "httpd: Could not mmap %s\n", mfile);
	    exit(APEXIT_INIT);
	}
	close(fd);
	unlink(mfile);
    }
#else
    m = mmap((caddr_t) 0, SCOREBOARD_SIZE,
	     PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
#endif
    if (m == (caddr_t) - 1) {
	perror("mmap");
