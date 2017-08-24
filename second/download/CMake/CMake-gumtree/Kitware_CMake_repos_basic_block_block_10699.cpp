(simple) {
			f->coders[i].numInStreams = 1;
			f->coders[i].numOutStreams = 1;
		} else {
			if (parse_7zip_uint64(
			    a, &(f->coders[i].numInStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f->coders[i].numInStreams)
				return (-1);
			if (parse_7zip_uint64(
			    a, &(f->coders[i].numOutStreams)) < 0)
				return (-1);
			if (UMAX_ENTRY < f->coders[i].numOutStreams)
				return (-1);
		}