static int will_fetch(struct ref **head, const unsigned char *sha1)
{
	struct ref *rm = *head;
	while (rm) {
		if (!hashcmp(rm->old_oid.hash, sha1))
			return 1;
		rm = rm->next;
	}
	return 0;
}