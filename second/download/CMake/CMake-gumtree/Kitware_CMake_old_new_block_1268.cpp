{
    fprintf(stderr, "tar_append_eof(): %s\n", strerror(errno));
    tar_close(t);
    return false;
    }