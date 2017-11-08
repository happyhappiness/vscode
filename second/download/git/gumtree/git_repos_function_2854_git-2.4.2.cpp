static void add_child(struct child_process *cld, struct sockaddr *addr, socklen_t addrlen)
{
	struct child *newborn, **cradle;

	newborn = xcalloc(1, sizeof(*newborn));
	live_children++;
	memcpy(&newborn->cld, cld, sizeof(*cld));
	memcpy(&newborn->address, addr, addrlen);
	for (cradle = &firstborn; *cradle; cradle = &(*cradle)->next)
		if (!addrcmp(&(*cradle)->address, &newborn->address))
			break;
	newborn->next = *cradle;
	*cradle = newborn;
}