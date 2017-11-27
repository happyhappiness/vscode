static int openvpn_shutdown (void)
{
	int i;

	for (i = 0; i < vpn_num; i++)
	{
		sfree (vpn_list[i]->file);
		sfree (vpn_list[i]);
	}

	sfree (vpn_list);

	return (0);
}