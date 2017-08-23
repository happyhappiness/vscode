(void)sprintf(ar_hb, HDR1, AR_EFMT1, (int)lname, (long int)sb->st_mtime,
                  (unsigned)uid, (unsigned)gid, (unsigned)sb->st_mode,
                  (long long)sb->st_size + lname, ARFMAG)