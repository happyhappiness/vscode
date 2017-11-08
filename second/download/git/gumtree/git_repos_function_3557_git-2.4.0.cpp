static int pool_entry_cmp(const struct pool_entry *e1,
			  const struct pool_entry *e2,
			  const unsigned char *keydata)
{
	return e1->data != keydata &&
	       (e1->len != e2->len || memcmp(e1->data, keydata, e1->len));
}