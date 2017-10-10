#include "cache.h"

int copy_fd(int ifd, int ofd)
{
	while (1) {
		char buffer[8192];
		ssize_t len = xread(ifd, buffer, sizeof(buffer));
		if (!len)
			break;
		if (len < 0) {
			return error("copy-fd: read returned %s",
				     strerror(errno));
		}
		if (write_in_full(ofd, buffer, len) < 0)
			return error("copy-fd: write returned %s",
				     strerror(errno));
	}
	return 0;
}

static int copy_times(const char *dst, const char *src)
{
	struct stat st;
