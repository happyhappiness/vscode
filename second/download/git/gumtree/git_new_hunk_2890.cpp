		for (i = 0; i < num_rev; i++) {
			int j;
			int is_head = rev_is_head(head,
						  head_len,
						  ref_name[i],
						  head_oid.hash,
						  rev[i]->object.oid.hash);
			if (extra < 0)
				printf("%c [%s] ",
				       is_head ? '*' : ' ', ref_name[i]);
			else {
				for (j = 0; j < i; j++)
					putchar(' ');
