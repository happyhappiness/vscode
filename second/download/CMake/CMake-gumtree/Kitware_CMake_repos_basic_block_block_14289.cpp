handle = CreateFileA(path, 0, 0, NULL,
				    OPEN_EXISTING,
				    FILE_FLAG_BACKUP_SEMANTICS |
				    FILE_ATTRIBUTE_READONLY,
					NULL)