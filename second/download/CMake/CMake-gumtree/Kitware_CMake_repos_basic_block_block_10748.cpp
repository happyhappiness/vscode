(pack = 1; pack < f[i].numUnpackStreams; pack++) {
				if (parse_7zip_uint64(a, usizes) < 0)
					return (-1);
				sum += *usizes++;
			}