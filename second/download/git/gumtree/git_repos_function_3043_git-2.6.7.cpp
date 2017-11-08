static void kill_some_child(void)
{
	const struct child *blanket, *next;

	if (!(blanket = firstborn))
		return;

	for (; (next = blanket->next); blanket = next)
		if (!addrcmp(&blanket->address, &next->address)) {
			kill(blanket->cld.pid, SIGTERM);
			break;
		}
}