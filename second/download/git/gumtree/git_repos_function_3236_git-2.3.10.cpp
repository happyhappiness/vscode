static int read_message(FILE *f, struct strbuf *all_msgs)
{
	do {
		if (strbuf_fread(all_msgs, CHUNKSIZE, f) <= 0)
			break;
	} while (!feof(f));

	return ferror(f) ? -1 : 0;
}