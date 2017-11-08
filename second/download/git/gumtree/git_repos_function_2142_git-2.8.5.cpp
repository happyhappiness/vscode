void clear_mailinfo(struct mailinfo *mi)
{
	int i;

	strbuf_release(&mi->name);
	strbuf_release(&mi->email);
	strbuf_release(&mi->charset);
	free(mi->message_id);

	for (i = 0; mi->p_hdr_data[i]; i++)
		strbuf_release(mi->p_hdr_data[i]);
	free(mi->p_hdr_data);
	for (i = 0; mi->s_hdr_data[i]; i++)
		strbuf_release(mi->s_hdr_data[i]);
	free(mi->s_hdr_data);

	while (mi->content < mi->content_top) {
		free(*(mi->content_top));
		mi->content_top--;
	}

	strbuf_release(&mi->log_message);
}