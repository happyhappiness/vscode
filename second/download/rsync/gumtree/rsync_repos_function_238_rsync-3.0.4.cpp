static void rsync_xal_free(item_list *xalp)
{
	size_t i;
	rsync_xa *rxas = xalp->items;

	for (i = 0; i < xalp->count; i++) {
		free(rxas[i].datum);
		/*free(rxas[i].name);*/
	}
	xalp->count = 0;
}