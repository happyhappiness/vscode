static int vserver_init(void) {
  /* XXX Should we check for getpagesize () in configure?
   * What's the right thing to do, if there is no getpagesize ()? */
  pagesize = getpagesize();

  return 0;
}