
static void pp_output(struct parallel_processes *pp)
{
	int i = pp->output_owner;
	if (pp->children[i].state == GIT_CP_WORKING &&
	    pp->children[i].err.len) {
		strbuf_write(&pp->children[i].err, stderr);
		strbuf_reset(&pp->children[i].err);
	}
}

static int pp_collect_finished(struct parallel_processes *pp)
{
