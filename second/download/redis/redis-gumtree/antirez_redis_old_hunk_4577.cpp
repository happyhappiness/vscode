        if (fd > STDERR_FILENO) close(fd);
    }
    /* Try to write the pid file */
    fp = fopen("/var/run/redis.pid","w");
    if (fp) {
        fprintf(fp,"%d\n",getpid());
        fclose(fp);
