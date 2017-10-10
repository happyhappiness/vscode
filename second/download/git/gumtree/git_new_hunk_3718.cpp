#include "cache.h"
#include "run-command.h"
#include "sigchain.h"
#include "connected.h"
#include "transport.h"

/*
 * If we feed all the commits we want to verify to this command
 *
 *  $ git rev-list --objects --stdin --not --all
 *
 * and if it does not error out, that means everything reachable from
 * these commits locally exists and is connected to our existing refs.
 * Note that this does _not_ validate the individual objects.
 *
 * Returns 0 if everything is connected, non-zero otherwise.
 */
int check_connected(sha1_iterate_fn fn, void *cb_data,
		    struct check_connected_options *opt)
{
	struct child_process rev_list = CHILD_PROCESS_INIT;
	struct check_connected_options defaults = CHECK_CONNECTED_INIT;
	char commit[41];
	unsigned char sha1[20];
	int err = 0;
	struct packed_git *new_pack = NULL;
	struct transport *transport;
	size_t base_len;

	if (!opt)
		opt = &defaults;
	transport = opt->transport;

	if (fn(cb_data, sha1)) {
		if (opt->err_fd)
			close(opt->err_fd);
		return err;
	}

	if (transport && transport->smart_options &&
	    transport->smart_options->self_contained_and_connected &&
	    transport->pack_lockfile &&
	    strip_suffix(transport->pack_lockfile, ".keep", &base_len)) {
		struct strbuf idx_file = STRBUF_INIT;
		strbuf_add(&idx_file, transport->pack_lockfile, base_len);
		strbuf_addstr(&idx_file, ".idx");
		new_pack = add_packed_git(idx_file.buf, idx_file.len, 1);
		strbuf_release(&idx_file);
	}

	if (opt->shallow_file) {
		argv_array_push(&rev_list.args, "--shallow-file");
		argv_array_push(&rev_list.args, opt->shallow_file);
	}
	argv_array_push(&rev_list.args,"rev-list");
	argv_array_push(&rev_list.args, "--objects");
	argv_array_push(&rev_list.args, "--stdin");
	argv_array_push(&rev_list.args, "--not");
	argv_array_push(&rev_list.args, "--all");
	argv_array_push(&rev_list.args, "--quiet");
	if (opt->progress)
		argv_array_pushf(&rev_list.args, "--progress=%s",
				 _("Checking connectivity"));

	rev_list.git_cmd = 1;
	rev_list.in = -1;
	rev_list.no_stdout = 1;
	if (opt->err_fd)
		rev_list.err = opt->err_fd;
	else
		rev_list.no_stderr = opt->quiet;

	if (start_command(&rev_list))
		return error(_("Could not run 'git rev-list'"));

	sigchain_push(SIGPIPE, SIG_IGN);

	commit[40] = '\n';
