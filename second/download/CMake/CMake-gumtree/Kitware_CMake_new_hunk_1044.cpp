			}

			break;

		} else {

			la_dosmaperr(GetLastError());

			archive_set_error(&a->archive, errno,

			    "DeviceIoControl Failed: %lu", GetLastError());

			exit_sts = ARCHIVE_FAILED;

			goto exit_setup_sparse;
