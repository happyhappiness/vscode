(iso9660->zisofs.magic_cnt < magic_max) {
			size_t l;

			l = sizeof(iso9660->zisofs.magic_buffer)
			    - iso9660->zisofs.magic_cnt;
			if (l > s)
				l = s;
			memcpy(iso9660->zisofs.magic_buffer
			    + iso9660->zisofs.magic_cnt, buff, l);
			iso9660->zisofs.magic_cnt += (int)l;
			if (iso9660->zisofs.magic_cnt < magic_max)
				return;
		}