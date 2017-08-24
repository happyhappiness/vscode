(attr) {
			if (parse_7zip_uint64(
			    a, &(f->coders[i].propertiesSize)) < 0)
				return (-1);
			if ((p = header_bytes(
			    a, (size_t)f->coders[i].propertiesSize)) == NULL)
				return (-1);
			f->coders[i].properties =
			    malloc((size_t)f->coders[i].propertiesSize);
			if (f->coders[i].properties == NULL)
				return (-1);
			memcpy(f->coders[i].properties, p,
			    (size_t)f->coders[i].propertiesSize);
		}