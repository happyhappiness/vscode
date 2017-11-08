int is_a_socket(int fd)
{
	int v;
	socklen_t l = sizeof (int);

	/* Parameters to getsockopt, setsockopt etc are very
	 * unstandardized across platforms, so don't be surprised if
	 * there are compiler warnings on e.g. SCO OpenSwerver or AIX.
	 * It seems they all eventually get the right idea.
	 *
	 * Debian says: ``The fifth argument of getsockopt and
	 * setsockopt is in reality an int [*] (and this is what BSD
	 * 4.* and libc4 and libc5 have).  Some POSIX confusion
	 * resulted in the present socklen_t.  The draft standard has
	 * not been adopted yet, but glibc2 already follows it and
	 * also has socklen_t [*]. See also accept(2).''
	 *
	 * We now return to your regularly scheduled programming.  */
	return getsockopt(fd, SOL_SOCKET, SO_TYPE, (char *)&v, &l) == 0;
}