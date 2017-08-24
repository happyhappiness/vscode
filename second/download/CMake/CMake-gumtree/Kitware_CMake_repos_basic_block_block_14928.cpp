((p->fixup & TODO_MAC_METADATA) == 0 ||
			    p->mac_metadata == NULL ||
			    p->mac_metadata_size == 0)
#endif
				archive_write_disk_set_acls(&a->archive,
				    -1, p->name, &p->acl)