#include "cache.h"
#include "pack.h"

static const char show_index_usage[] =
"git show-index";

int cmd_main(int argc, const char **argv)
{
	int i;
	unsigned nr;
	unsigned int version;
	static unsigned int top_index[256];

	if (argc != 1)
		usage(show_index_usage);
	if (fread(top_index, 2 * 4, 1, stdin) != 1)
		die("unable to read header");
	if (top_index[0] == htonl(PACK_IDX_SIGNATURE)) {
		version = ntohl(top_index[1]);
