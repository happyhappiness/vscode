(version == 1) {
					if (data_length >= 8)
						file->mode
						    = toi(data, 4);
					if (data_length >= 16)
						file->nlinks
						    = toi(data + 8, 4);
					if (data_length >= 24)
						file->uid
						    = toi(data + 16, 4);
					if (data_length >= 32)
						file->gid
						    = toi(data + 24, 4);
					if (data_length >= 40)
						file->number
						    = toi(data + 32, 4);
					iso9660->seenRockridge = 1;
				}