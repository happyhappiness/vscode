    lseek(fd, 0, SEEK_SET);

    rc = _locking(fd, _LK_UNLCK, 1);

    lseek(fd, 0, SEEK_END);

#endif



    if (rc < 0) {

        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

                     "mod_rewrite: failed to unlock file descriptor");

        exit(1);

    }

}



/*

-- apache_1.3.1/src/modules/standard/mod_rewrite.h	1998-07-13 19:32:46.000000000 +0800

