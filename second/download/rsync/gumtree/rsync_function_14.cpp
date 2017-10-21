void usage(void)
{
  fprintf(stderr,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",VERSION);
  fprintf(stderr,"Usage:\t%s [options] src user@host:dest\nOR",RSYNC_NAME);
  fprintf(stderr,"\t%s [options] user@host:src dest\n\n",RSYNC_NAME);
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"-v       : increase verbosity\n");
  fprintf(stderr,"-c       : always checksum\n");
  fprintf(stderr,"-a       : archive mode (same as -rlptDog)\n");
  fprintf(stderr,"-r       : recurse into directories\n");
  fprintf(stderr,"-b       : make backups (default ~ extension)\n");
  fprintf(stderr,"-u       : update only (don't overwrite newer files)\n");
  fprintf(stderr,"-l       : preserve soft links\n");
  fprintf(stderr,"-p       : preserve permissions\n");
  fprintf(stderr,"-o       : preserve owner (root only)\n");
  fprintf(stderr,"-g       : preserve group\n");
  fprintf(stderr,"-D       : preserve devices (root only)\n");
  fprintf(stderr,"-t       : preserve times\n");  
  fprintf(stderr,"-e cmd   : specify rsh replacement\n");
}