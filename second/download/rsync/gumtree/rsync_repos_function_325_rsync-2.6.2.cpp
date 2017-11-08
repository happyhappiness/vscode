void usage(enum logcode F)
{
  print_rsync_version(F);

  rprintf(F,"\nrsync is a file transfer program capable of efficient remote update\nvia a fast differencing algorithm.\n\n");

  rprintf(F,"Usage: rsync [OPTION]... SRC [SRC]... [USER@]HOST:DEST\n");
  rprintf(F,"  or   rsync [OPTION]... [USER@]HOST:SRC DEST\n");
  rprintf(F,"  or   rsync [OPTION]... SRC [SRC]... DEST\n");
  rprintf(F,"  or   rsync [OPTION]... [USER@]HOST::SRC [DEST]\n");
  rprintf(F,"  or   rsync [OPTION]... SRC [SRC]... [USER@]HOST::DEST\n");
  rprintf(F,"  or   rsync [OPTION]... rsync://[USER@]HOST[:PORT]/SRC [DEST]\n");
  rprintf(F,"  or   rsync [OPTION]... SRC [SRC]... rsync://[USER@]HOST[:PORT]/DEST\n");
  rprintf(F,"SRC on single-colon remote HOST will be expanded by remote shell\n");
  rprintf(F,"SRC on server remote HOST may contain shell wildcards or multiple\n");
  rprintf(F,"  sources separated by space as long as they have same top-level\n");
  rprintf(F,"\nOptions\n");
  rprintf(F," -v, --verbose               increase verbosity\n");
  rprintf(F," -q, --quiet                 decrease verbosity\n");
  rprintf(F," -c, --checksum              always checksum\n");
  rprintf(F," -a, --archive               archive mode, equivalent to -rlptgoD\n");
  rprintf(F," -r, --recursive             recurse into directories\n");
  rprintf(F," -R, --relative              use relative path names\n");
  rprintf(F,"     --no-relative           turn off --relative\n");
  rprintf(F,"     --no-implied-dirs       don't send implied dirs with -R\n");
  rprintf(F," -b, --backup                make backups (see --suffix & --backup-dir)\n");
  rprintf(F,"     --backup-dir            make backups into this directory\n");
  rprintf(F,"     --suffix=SUFFIX         backup suffix (default %s w/o --backup-dir)\n",BACKUP_SUFFIX);
  rprintf(F," -u, --update                update only (don't overwrite newer files)\n");
  rprintf(F," -l, --links                 copy symlinks as symlinks\n");
  rprintf(F," -L, --copy-links            copy the referent of all symlinks\n");
  rprintf(F,"     --copy-unsafe-links     copy the referent of \"unsafe\" symlinks\n");
  rprintf(F,"     --safe-links            ignore \"unsafe\" symlinks\n");
  rprintf(F," -H, --hard-links            preserve hard links\n");
  rprintf(F," -p, --perms                 preserve permissions\n");
  rprintf(F," -o, --owner                 preserve owner (root only)\n");
  rprintf(F," -g, --group                 preserve group\n");
  rprintf(F," -D, --devices               preserve devices (root only)\n");
  rprintf(F," -t, --times                 preserve times\n");
  rprintf(F," -S, --sparse                handle sparse files efficiently\n");
  rprintf(F," -n, --dry-run               show what would have been transferred\n");
  rprintf(F," -W, --whole-file            copy whole files, no incremental checks\n");
  rprintf(F,"     --no-whole-file         turn off --whole-file\n");
  rprintf(F," -x, --one-file-system       don't cross filesystem boundaries\n");
  rprintf(F," -B, --block-size=SIZE       checksum blocking size (default %d)\n",BLOCK_SIZE);
  rprintf(F," -e, --rsh=COMMAND           specify the remote shell\n");
  rprintf(F,"     --rsync-path=PATH       specify path to rsync on the remote machine\n");
  rprintf(F,"     --existing              only update files that already exist\n");
  rprintf(F,"     --ignore-existing       ignore files that already exist on receiving side\n");
  rprintf(F,"     --delete                delete files that don't exist on the sending side\n");
  rprintf(F,"     --delete-excluded       also delete excluded files on the receiving side\n");
  rprintf(F,"     --delete-after          receiver deletes after transferring, not before\n");
  rprintf(F,"     --ignore-errors         delete even if there are I/O errors\n");
  rprintf(F,"     --max-delete=NUM        don't delete more than NUM files\n");
  rprintf(F,"     --partial               keep partially transferred files\n");
  rprintf(F,"     --force                 force deletion of directories even if not empty\n");
  rprintf(F,"     --numeric-ids           don't map uid/gid values by user/group name\n");
  rprintf(F,"     --timeout=TIME          set I/O timeout in seconds\n");
  rprintf(F," -I, --ignore-times          turn off mod time & file size quick check\n");
  rprintf(F,"     --size-only             ignore mod time for quick check (use size)\n");
  rprintf(F,"     --modify-window=NUM     compare mod times with reduced accuracy\n");
  rprintf(F," -T  --temp-dir=DIR          create temporary files in directory DIR\n");
  rprintf(F,"     --compare-dest=DIR      also compare destination files relative to DIR\n");
  rprintf(F,"     --link-dest=DIR         create hardlinks to DIR for unchanged files\n");
  rprintf(F," -P                          equivalent to --partial --progress\n");
  rprintf(F," -z, --compress              compress file data\n");
  rprintf(F," -C, --cvs-exclude           auto ignore files in the same way CVS does\n");
  rprintf(F,"     --exclude=PATTERN       exclude files matching PATTERN\n");
  rprintf(F,"     --exclude-from=FILE     exclude patterns listed in FILE\n");
  rprintf(F,"     --include=PATTERN       don't exclude files matching PATTERN\n");
  rprintf(F,"     --include-from=FILE     don't exclude patterns listed in FILE\n");
  rprintf(F,"     --files-from=FILE       read FILE for list of source-file names\n");
  rprintf(F," -0  --from0                 all *-from file lists are delimited by nulls\n");
  rprintf(F,"     --version               print version number\n");
  rprintf(F,"     --daemon                run as an rsync daemon\n");
  rprintf(F,"     --no-detach             do not detach from the parent\n");
  rprintf(F,"     --address=ADDRESS       bind to the specified address\n");
  rprintf(F,"     --config=FILE           specify alternate rsyncd.conf file\n");
  rprintf(F,"     --port=PORT             specify alternate rsyncd port number\n");
  rprintf(F,"     --blocking-io           use blocking I/O for the remote shell\n");
  rprintf(F,"     --no-blocking-io        turn off --blocking-io\n");
  rprintf(F,"     --stats                 give some file transfer stats\n");
  rprintf(F,"     --progress              show progress during transfer\n");
  rprintf(F,"     --log-format=FORMAT     log file transfers using specified format\n");
  rprintf(F,"     --password-file=FILE    get password from FILE\n");
  rprintf(F,"     --bwlimit=KBPS          limit I/O bandwidth, KBytes per second\n");
  rprintf(F,"     --write-batch=PREFIX    write batch fileset starting with PREFIX\n");
  rprintf(F,"     --read-batch=PREFIX     read batch fileset starting with PREFIX\n");
  rprintf(F," -h, --help                  show this help screen\n");
#ifdef INET6
  rprintf(F," -4                          prefer IPv4\n");
  rprintf(F," -6                          prefer IPv6\n");
#endif

  rprintf(F,"\n");

  rprintf(F,"\nPlease see the rsync(1) and rsyncd.conf(5) man pages for full documentation\n");
  rprintf(F,"See http://rsync.samba.org/ for updates, bug reports, and answers\n");
}