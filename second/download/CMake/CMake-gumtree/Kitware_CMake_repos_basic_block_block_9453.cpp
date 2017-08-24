{
			int stflags;
			r = ioctl(fd,
#if defined(FS_IOC_GETFLAGS)
			    FS_IOC_GETFLAGS,
#else
			    EXT2_IOC_GETFLAGS,
#endif
			    &stflags);
			if (r == 0 && stflags != 0)
				archive_entry_set_fflags(entry, stflags, 0);
		}