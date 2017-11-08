static void decode_transfer_encoding(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf *ret;

	switch (mi->transfer_encoding) {
	case TE_QP:
		ret = decode_q_segment(line, 0);
		break;
	case TE_BASE64:
		ret = decode_b_segment(line);
		break;
	case TE_DONTCARE:
	default:
		return;
	}
	strbuf_reset(line);
	strbuf_addbuf(line, ret);
	strbuf_release(ret);
	free(ret);
}