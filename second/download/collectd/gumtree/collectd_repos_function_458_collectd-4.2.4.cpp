static void
uuidcache_addentry(char *device, char *label, char *uuid)
{
	struct uuidCache_s *last;

	if(!uuidCache) {
		last = uuidCache = smalloc(sizeof(*uuidCache));
	} else {
		for(last = uuidCache; last->next; last = last->next);
		last->next = smalloc(sizeof(*uuidCache));
		last = last->next;
	}
	last->next = NULL;
	last->device = device;
	last->label = label;
	memcpy(last->uuid, uuid, sizeof(last->uuid));
}