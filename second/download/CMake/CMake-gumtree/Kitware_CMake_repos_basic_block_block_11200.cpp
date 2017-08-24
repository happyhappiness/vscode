(bytes_avail <= mszip) {
				if (mszip == 2) {
					if (cab->stream.next_in[0] != 0x43)
						goto nomszip;
					if (bytes_avail > 1 &&
					    cab->stream.next_in[1] != 0x4b)
						goto nomszip;
				} else if (cab->stream.next_in[0] != 0x4b)
					goto nomszip;
				cfdata->unconsumed = bytes_avail;
				cfdata->sum_ptr = d;
				if (cab_minimum_consume_cfdata(
				    a, cfdata->unconsumed) < 0) {
					*avail = ARCHIVE_FATAL;
					return (NULL);
				}
				mszip -= (int)bytes_avail;
				continue;
			}