void add_fill_function(void *data, int (*fill)(void *))
{
	struct fill_chain *new = xmalloc(sizeof(*new));
	struct fill_chain **linkp = &fill_cfg;
	new->data = data;
	new->fill = fill;
	new->next = NULL;
	while (*linkp)
		linkp = &(*linkp)->next;
	*linkp = new;
}