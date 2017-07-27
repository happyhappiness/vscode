(void)sprintf(ar_hb, HDR2, name, (long int)sb->st_mtime, (unsigned)uid,
                  (unsigned)gid, (unsigned)sb->st_mode, (long long)sb->st_size,
                  ARFMAG)