    lseek(fd, 0, SEEK_SET);
    rc = _locking(fd, _LK_LOCK, 1);
    lseek(fd, 0, SEEK_END);
#endif

    if (rc < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                     "mod_rewrite: failed to lock file descriptor");
        exit(1);
    }
    return;
}

