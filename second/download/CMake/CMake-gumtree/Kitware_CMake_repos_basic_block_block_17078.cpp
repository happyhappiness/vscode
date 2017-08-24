{
			/* URL encoding is '%' followed by two hex digits */
			*d++ = '%';
			*d++ = "0123456789ABCDEF"[0x0f & (*s >> 4)];
			*d++ = "0123456789ABCDEF"[0x0f & *s];
		}