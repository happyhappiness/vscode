 *
 * Copyright (c) 2014 Michael J Gruber <git@drmicha.warpmail.net>
 *
 * Based on git-verify-tag
 */
#include "cache.h"
#include "config.h"
#include "builtin.h"
#include "commit.h"
#include "run-command.h"
#include <signal.h>
#include "parse-options.h"
#include "gpg-interface.h"

static const char * const verify_commit_usage[] = {
		N_("git verify-commit [-v | --verbose] <commit>..."),
		NULL
};

static int run_gpg_verify(const struct object_id *oid, const char *buf, unsigned long size, unsigned flags)
{
	struct signature_check signature_check;
	int ret;

	memset(&signature_check, 0, sizeof(signature_check));

	ret = check_commit_signature(lookup_commit(oid), &signature_check);
	print_signature_buffer(&signature_check, flags);

	signature_check_clear(&signature_check);
	return ret;
}

static int verify_commit(const char *name, unsigned flags)
{
	enum object_type type;
	struct object_id oid;
	char *buf;
	unsigned long size;
	int ret;

	if (get_oid(name, &oid))
		return error("commit '%s' not found.", name);

	buf = read_sha1_file(oid.hash, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);
	if (type != OBJ_COMMIT)
		return error("%s: cannot verify a non-commit object of type %s.",
				name, typename(type));

	ret = run_gpg_verify(&oid, buf, size, flags);

	free(buf);
	return ret;
}

static int git_verify_commit_config(const char *var, const char *value, void *cb)
