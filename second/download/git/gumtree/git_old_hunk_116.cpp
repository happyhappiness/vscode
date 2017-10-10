#include "builtin.h"

static void flush_current_id(int patchlen, unsigned char *id, git_SHA_CTX *c)
{
	unsigned char result[20];
	char name[50];

	if (!patchlen)
		return;

	git_SHA1_Final(result, c);
	memcpy(name, sha1_to_hex(id), 41);
	printf("%s %s\n", sha1_to_hex(result), name);
	git_SHA1_Init(c);
}

static int remove_space(char *line)
{
	char *src = line;
	char *dst = line;
