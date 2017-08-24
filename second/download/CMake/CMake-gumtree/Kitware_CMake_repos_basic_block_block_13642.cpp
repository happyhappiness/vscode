{
		struct zip * zip = (struct zip *)_a->format->data;
		if (zip) {
			return zip->has_encrypted_entries;
		}
	}