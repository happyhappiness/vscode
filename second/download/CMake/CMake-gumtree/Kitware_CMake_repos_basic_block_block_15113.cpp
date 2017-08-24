(!wcsncmp(target,L"\\\\?\\", 4)) {
			target += 4;
			if (IS_UNC(target))
				target += 4;
		}