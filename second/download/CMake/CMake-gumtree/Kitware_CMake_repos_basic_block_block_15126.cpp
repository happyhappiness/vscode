{
			DWORD dmy;
			/* Mark this file as sparse. */
			DeviceIoControl(a->fh, FSCTL_SET_SPARSE,
			    NULL, 0, NULL, 0, &dmy, NULL);
		}