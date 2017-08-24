{
	if (unlikely(dict->pos == dict->limit))
		return true;

	dict->buf[dict->pos++] = byte;

	if (dict->pos > dict->full)
		dict->full = dict->pos;

	return false;
}