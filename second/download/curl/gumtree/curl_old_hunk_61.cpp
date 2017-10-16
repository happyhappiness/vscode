
#ifdef DPRINTF_DEBUG
int main()
{
  char buffer[129];
  char *ptr;
#ifdef HAVE_LONGLONG
  long long hullo;
  dprintf("%3$12s %1$s %2$qd %4$d\n", "daniel", hullo, "stenberg", 65);
#endif

  mprintf("%3d %5d\n", 10, 1998);
  
  ptr=maprintf("test this then baby %s%s%s%s%s%s %d %d %d loser baby get a hit in yer face now!", "", "pretty long string pretty long string pretty long string pretty long string pretty long string", "/", "/", "/", "pretty long string", 1998, 1999, 2001);

  puts(ptr);

  memset(ptr, 55, strlen(ptr)+1);

  free(ptr);

#if 1
  mprintf(buffer, "%s %s %d", "daniel", "stenberg", 19988);
  puts(buffer);

  mfprintf(stderr, "%s %#08x\n", "dummy", 65);

  printf("%s %#08x\n", "dummy", 65);
  {
    double tryout = 3.14156592;
    mprintf(buffer, "%.2g %G %f %e %E", tryout, tryout, tryout, tryout, tryout);
    puts(buffer);
    printf("%.2g %G %f %e %E\n", tryout, tryout, tryout, tryout, tryout);
  }
#endif

  return 0;
