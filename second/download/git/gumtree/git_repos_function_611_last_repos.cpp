void show_ref_array_item(struct ref_array_item *info,
			 const struct ref_format *format)
{
	struct strbuf final_buf = STRBUF_INIT;

	format_ref_array_item(info, format, &final_buf);
	fwrite(final_buf.buf, 1, final_buf.len, stdout);
	strbuf_release(&final_buf);
	putchar('\n');
}