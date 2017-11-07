static void remove_sequencer_state(void)
{
	struct strbuf seq_dir = STRBUF_INIT;

	strbuf_addstr(&seq_dir, git_path(SEQ_DIR));
	remove_dir_recursively(&seq_dir, 0);
	strbuf_release(&seq_dir);
}