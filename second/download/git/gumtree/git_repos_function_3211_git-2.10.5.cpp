static void flush_output(struct merge_options *o)
{
	if (o->buffer_output < 2 && o->obuf.len) {
		fputs(o->obuf.buf, stdout);
		strbuf_reset(&o->obuf);
	}
}