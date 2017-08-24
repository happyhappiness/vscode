{
		bst = archive_le32dec(p);
		if (bst != doff)
			return;/* Invalid data. */
		p += 4;
		bed = archive_le32dec(p);
		if (bed < bst || bed > entry_size)
			return;/* Invalid data. */
		doff += bed - bst;
		_ceil--;
	}