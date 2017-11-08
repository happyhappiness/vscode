struct strbuf *alt_scratch_buf(struct alternate_object_database *alt)
{
	strbuf_setlen(&alt->scratch, alt->base_len);
	return &alt->scratch;
}