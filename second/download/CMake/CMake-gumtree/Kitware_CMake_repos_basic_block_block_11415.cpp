(ptn & bit) {
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