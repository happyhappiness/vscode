{
		uint16_t *p;
		int len, cnt;
		uint16_t bit;
		int extlen;
		struct htree_t *ht;

		if (bitlen[i] == 0)
			continue;
		/* Get a bit pattern */
		len = bitlen[i];
		ptn = bitptn[len];
		cnt = weight[len];
		if (len <= HTBL_BITS) {
			/* Calculate next bit pattern */
			if ((bitptn[len] = ptn + cnt) > tbl_size)
				return (0);/* Invalid */
			/* Update the table */
			p = &(tbl[ptn]);
			if (cnt > 7) {
				uint16_t *pc;

				cnt -= 8;
				pc = &p[cnt];
				pc[0] = (uint16_t)i;
				pc[1] = (uint16_t)i;
				pc[2] = (uint16_t)i;
				pc[3] = (uint16_t)i;
				pc[4] = (uint16_t)i;
				pc[5] = (uint16_t)i;
				pc[6] = (uint16_t)i;
				pc[7] = (uint16_t)i;
				if (cnt > 7) {
					cnt -= 8;
					memcpy(&p[cnt], pc,
						8 * sizeof(uint16_t));
					pc = &p[cnt];
					while (cnt > 15) {
						cnt -= 16;
						memcpy(&p[cnt], pc,
							16 * sizeof(uint16_t));
					}
				}
				if (cnt)
					memcpy(p, pc, cnt * sizeof(uint16_t));
			} else {
				while (cnt > 1) {
					p[--cnt] = (uint16_t)i;
					p[--cnt] = (uint16_t)i;
				}
				if (cnt)
					p[--cnt] = (uint16_t)i;
			}
			continue;
		}

		/*
		 * A bit length is too big to be housed to a direct table,
		 * so we use a tree model for its extra bits.
		 */
		bitptn[len] = ptn + cnt;
		bit = 1U << (diffbits -1);
		extlen = len - HTBL_BITS;
		
		p = &(tbl[ptn >> diffbits]);
		if (*p == 0) {
			*p = len_avail + hf->tree_used;
			ht = &(hf->tree[hf->tree_used++]);
			if (hf->tree_used > hf->tree_avail)
				return (0);/* Invalid */
			ht->left = 0;
			ht->right = 0;
		} else {
			if (*p < len_avail ||
			    *p >= (len_avail + hf->tree_used))
				return (0);/* Invalid */
			ht = &(hf->tree[*p - len_avail]);
		}
		while (--extlen > 0) {
			if (ptn & bit) {
				if (ht->left < len_avail) {
					ht->left = len_avail + hf->tree_used;
					ht = &(hf->tree[hf->tree_used++]);
					if (hf->tree_used > hf->tree_avail)
						return (0);/* Invalid */
					ht->left = 0;
					ht->right = 0;
				} else {
					ht = &(hf->tree[ht->left - len_avail]);
				}
			} else {
				if (ht->right < len_avail) {
					ht->right = len_avail + hf->tree_used;
					ht = &(hf->tree[hf->tree_used++]);
					if (hf->tree_used > hf->tree_avail)
						return (0);/* Invalid */
					ht->left = 0;
					ht->right = 0;
				} else {
					ht = &(hf->tree[ht->right - len_avail]);
				}
			}
			bit >>= 1;
		}
		if (ptn & bit) {
			if (ht->left != 0)
				return (0);/* Invalid */
			ht->left = (uint16_t)i;
		} else {
			if (ht->right != 0)
				return (0);/* Invalid */
			ht->right = (uint16_t)i;
		}
	}