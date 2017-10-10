#include "send-pack.h"
#include "quote.h"
#include "transport.h"
#include "version.h"
#include "sha1-array.h"
#include "gpg-interface.h"

static int feed_object(const unsigned char *sha1, int fd, int negative)
{
	char buf[42];

	if (negative && !has_sha1_file(sha1))
