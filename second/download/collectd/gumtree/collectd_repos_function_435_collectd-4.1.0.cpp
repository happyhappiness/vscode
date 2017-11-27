void cu_mount_freelist (cu_mount_t *list)
{
	cu_mount_t *this;
	cu_mount_t *next;

	DEBUG ("(list = 0x%p)", (void *) list);

	for (this = list; this != NULL; this = next)
	{
		next = this->next;

		sfree (this->dir);
		sfree (this->spec_device);
		sfree (this->device);
		sfree (this->type);
		sfree (this->options);
		sfree (this);
	}
}