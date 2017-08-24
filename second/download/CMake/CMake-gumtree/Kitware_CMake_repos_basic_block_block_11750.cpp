(version == 1 && data_length == 16) {
					file->rdev = toi(data,4);
					file->rdev <<= 32;
					file->rdev |= toi(data + 8, 4);
					iso9660->seenRockridge = 1;
				}