{
			HANDLE handle;

			if (ws != NULL)
				handle = CreateFileW(ws, 0, 0, NULL,
				    OPEN_EXISTING,
				    FILE_FLAG_BACKUP_SEMANTICS |
				    FILE_ATTRIBUTE_READONLY,
					NULL);
			else
				handle = CreateFileA(path, 0, 0, NULL,
				    OPEN_EXISTING,
				    FILE_FLAG_BACKUP_SEMANTICS |
				    FILE_ATTRIBUTE_READONLY,
					NULL);
			free(ws);
			if (handle == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				return (-1);
			}
			r = _open_osfhandle((intptr_t)handle, _O_RDONLY);
			return (r);
		}