(skip_bytes-- > 0) {
			code = getbits(self, 8);
			if (code < 0)
				return (code);
		}