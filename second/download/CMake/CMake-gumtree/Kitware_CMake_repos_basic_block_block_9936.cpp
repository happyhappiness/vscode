{
				t->sparse_list[j].offset =
				    t->sparse_list[j+1].offset;
				t->sparse_list[j].length =
				    t->sparse_list[j+1].length;
			}