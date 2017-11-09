static void mark_bad_packed_object(struct packed_git *p,
				   const unsigned char *sha1)
{
	unsigned i;
	for (i = 0; i < p->num_bad_objects; i++)
		if (!hashcmp(sha1, p->bad_object_sha1 + GIT_SHA1_RAWSZ * i))
			return;
	p->bad_object_sha1 = xrealloc(p->bad_object_sha1,
				      st_mult(GIT_MAX_RAWSZ,
					      st_add(p->num_bad_objects, 1)));
	hashcpy(p->bad_object_sha1 + GIT_SHA1_RAWSZ * p->num_bad_objects, sha1);
	p->num_bad_objects++;
}