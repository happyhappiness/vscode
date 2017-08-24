(ioctl(myfd,
#ifdef FS_IOC_SETFLAGS
	    FS_IOC_SETFLAGS,
#else
	    EXT2_IOC_SETFLAGS,
#endif
	    &newflags) >= 0)
		goto cleanup;