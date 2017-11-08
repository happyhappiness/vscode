void usage(int F)
{
  rprintf(F,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",
	  VERSION);

  rprintf(F,"rsync is a file transfer program capable of efficient remote update\nvia a fast differencing algorithm.\n\n");

  rprintf(F,"Usage: rsync [OPTION]... SRC [USER@]HOST:DEST\n");
  rprintf(F,"  or   rsync [OPTION]... [USER@]HOST:SRC DEST\n");
  rprintf(F,"  or   rsync [OPTION]... SRC DEST\n");
  rprintf(F,"  or   rsync [OPTION]... [USER@]HOST::SRC DEST\n");
  rprintf(F,"  or   rsync [OPTION]... SRC [USER@]HOST::DEST\n");
  rprintf(F,"\nOptions\n");
  rprintf(F," -v, --verbose               increase verbosity\n");
  rprintf(F," -c, --checksum              always checksum\n");
  rprintf(F," -a, --archive               archive mode\n");
  rprintf(F," -r, --recursive             recurse into directories\n");
  rprintf(F," -R, --relative              use relative path names\n");
  rprintf(F," -b, --backup                make backups (default ~ extension)\n");
  rprintf(F," -u, --update                update only (don't overwrite newer files)\n");
  rprintf(F," -l, --links                 preserve soft links\n");
  rprintf(F," -L, --copy-links            treat soft links like regular files\n");
  rprintf(F," -H, --hard-links            preserve hard links\n");
  rprintf(F," -p, --perms                 preserve permissions\n");
  rprintf(F," -o, --owner                 preserve owner (root only)\n");
  rprintf(F," -g, --group                 preserve group\n");
  rprintf(F," -D, --devices               preserve devices (root only)\n");
  rprintf(F," -t, --times                 preserve times\n");  
  rprintf(F," -S, --sparse                handle sparse files efficiently\n");
  rprintf(F," -n, --dry-run               show what would have been transferred\n");
  rprintf(F," -W, --whole-file            copy whole files, no incremental checks\n");
  rprintf(F," -x, --one-file-system       don't cross filesystem boundaries\n");
  rprintf(F," -B, --block-size=SIZE       checksum blocking size\n");  
  rprintf(F," -e, --rsh=COMMAND           specify rsh replacement\n");
  rprintf(F,"     --rsync-path=PATH       specify path to rsync on the remote machine\n");
  rprintf(F," -C, --cvs-exclude           auto ignore files in the same way CVS does\n");
  rprintf(F,"     --delete                delete files that don't exist on the sending side\n");
  rprintf(F,"     --force                 force deletion of directories even if not empty\n");
  rprintf(F,"     --numeric-ids           don't map uid/gid values by user/group name\n");
  rprintf(F,"     --timeout=TIME          set IO timeout in seconds\n");
  rprintf(F," -I, --ignore-times          don't exclude files that match length and time\n");
  rprintf(F," -T  --temp-dir=DIR          create temporary files in directory DIR\n");
  rprintf(F," -z, --compress              compress file data\n");
  rprintf(F,"     --exclude=PATTERN       exclude file FILE\n");
  rprintf(F,"     --exclude-from=PATTERN  exclude files listed in FILE\n");
  rprintf(F,"     --include=PATTERN       don't exclude file FILE\n");
  rprintf(F,"     --include-from=PATTERN  don't exclude files listed in FILE\n");
  rprintf(F,"     --suffix=SUFFIX         override backup suffix\n");  
  rprintf(F,"     --version               print version number\n");  
  rprintf(F,"     --daemon                run as a rsync daemon\n");  
  rprintf(F,"     --config=FILE           specify alternate rsyncd.conf file\n");  
  rprintf(F,"     --port=PORT             specify alternate rsyncd port number\n");
  rprintf(F,"     --stats                 give some file transfer stats\n");  
  rprintf(F," -h, --help                  show this help screen\n");

  rprintf(F,"\n");
  rprintf(F,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
  rprintf(F,"the block size defaults to %d\n",BLOCK_SIZE);  

  rprintf(F,"\nPlease see the rsync(1) and rsyncd.conf(5) man pages for full documentation\n");
  rprintf(F,"See http://samba.anu.edu.au/rsync/ for updates and bug reports\n");
}