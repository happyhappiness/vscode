		status = error("unable to parse %s header", sha1_to_hex(sha1));
	git_inflate_end(&stream);
	munmap(map, mapsize);
	if (status && oi->typep)
		*oi->typep = status;
	strbuf_release(&hdrbuf);
	return (status < 0) ? status : 0;
}

int sha1_object_info_extended(const unsigned char *sha1, struct object_info *oi, unsigned flags)
{
	struct cached_object *co;
	struct pack_entry e;
