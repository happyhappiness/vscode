static cu_mount_t *cu_mount_listmntent (void)
{
	cu_mount_t *last = *list;
	struct mntent *mnt;

	struct tabmntent *mntlist;
	if(listmntent(&mntlist, COLLECTD_MNTTAB, NULL, NULL) < 0) {
#if COLLECT_DEBUG
		char errbuf[1024];
		DEBUG("utils_mount: calling listmntent() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
#endif /* COLLECT_DEBUG */
	}

	for(struct tabmntent *p = mntlist; p; p = p->next) {
		char *loop = NULL, *device = NULL;

		mnt = p->ment;
		loop = cu_mount_getoptionvalue(mnt->mnt_opts, "loop=");
		if(loop == NULL) {   /* no loop= mount */
			device = get_device_name(mnt->mnt_fsname);
			if(device == NULL) {
				DEBUG("utils_mount: can't get devicename for fs (%s) %s (%s)"
					": ignored", mnt->mnt_type,
					mnt->mnt_dir, mnt->mnt_fsname);
				continue;
			}
		} else {
			device = loop;
		}
		if(*list == NULL) {
			*list = (cu_mount_t *)smalloc(sizeof(cu_mount_t));
			last = *list;
		} else {
			while(last->next != NULL) { /* is last really last? */
				last = last->next;
			}
			last->next = (cu_mount_t *)smalloc(sizeof(cu_mount_t));
			last = last->next;
		}
		last->dir = sstrdup(mnt->mnt_dir);
		last->spec_device = sstrdup(mnt->mnt_fsname);
		last->device = device;
		last->type = sstrdup(mnt->mnt_type);
		last->options = sstrdup(mnt->mnt_opts);
		last->next = NULL;
	} /* for(p = mntlist; p; p = p->next) */

	return(last);
}