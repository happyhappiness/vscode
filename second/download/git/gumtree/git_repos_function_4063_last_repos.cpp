static int recvline(struct helper_data *helper, struct strbuf *buffer)
{
	return recvline_fh(helper->out, buffer, helper->name);
}