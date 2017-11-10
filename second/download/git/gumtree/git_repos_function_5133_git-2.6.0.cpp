static void unlock_pack(void)
{
	if (gtransport)
		transport_unlock_pack(gtransport);
	if (gsecondary)
		transport_unlock_pack(gsecondary);
}