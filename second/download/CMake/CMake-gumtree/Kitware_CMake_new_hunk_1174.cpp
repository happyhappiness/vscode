                  (long long)sb->st_size + lname, ARFMAG);
    else {
      lname = 0;
      (void)sprintf(ar_hb, HDR2, name,
                    (long int)sb->st_mtime, uid, gid, sb->st_mode,
                    (long long)sb->st_size, ARFMAG);
      }
    off_t size = sb->st_size;
