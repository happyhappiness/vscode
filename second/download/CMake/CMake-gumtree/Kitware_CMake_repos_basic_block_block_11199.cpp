(mszip == 1 && cab->stream.next_in[0] != 0x4b)
				goto nomszip;
			else if (cab->stream.next_in[0] != 0x43 ||
			    cab->stream.next_in[1] != 0x4b)
				goto nomszip;