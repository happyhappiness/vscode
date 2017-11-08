int ewah_serialize_strbuf(struct ewah_bitmap *self, struct strbuf *sb)
{
	return ewah_serialize_to(self, write_strbuf, sb);
}