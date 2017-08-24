(ptn & bit) {
			if (ht->left != 0)
				return (0);/* Invalid */
			ht->left = (uint16_t)i;
		} else {
			if (ht->right != 0)
				return (0);/* Invalid */
			ht->right = (uint16_t)i;
		}