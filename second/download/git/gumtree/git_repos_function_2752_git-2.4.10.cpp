static int rerere_file_getline(struct strbuf *sb, struct rerere_io *io_)
{
	struct rerere_io_file *io = (struct rerere_io_file *)io_;
	return strbuf_getwholeline(sb, io->input, '\n');
}