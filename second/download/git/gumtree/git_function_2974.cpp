static void pp_output(struct parallel_processes *pp)
{
	int i = pp->output_owner;
	if (pp->children[i].state == GIT_CP_WORKING &&
	    pp->children[i].err.len) {
		fputs(pp->children[i].err.buf, stderr);
		strbuf_reset(&pp->children[i].err);
	}
}