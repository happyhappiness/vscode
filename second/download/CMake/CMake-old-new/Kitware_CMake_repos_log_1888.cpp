char *tmp = aprintf("statvfs:\n"
                            "f_bsize: %llu\n" "f_frsize: %llu\n"
                            "f_blocks: %llu\n" "f_bfree: %llu\n"
                            "f_bavail: %llu\n" "f_files: %llu\n"
                            "f_ffree: %llu\n" "f_favail: %llu\n"
                            "f_fsid: %llu\n" "f_flag: %llu\n"
                            "f_namemax: %llu\n",
                            statvfs.f_bsize, statvfs.f_frsize,
                            statvfs.f_blocks, statvfs.f_bfree,
                            statvfs.f_bavail, statvfs.f_files,
                            statvfs.f_ffree, statvfs.f_favail,
                            statvfs.f_fsid, statvfs.f_flag,
                            statvfs.f_namemax);