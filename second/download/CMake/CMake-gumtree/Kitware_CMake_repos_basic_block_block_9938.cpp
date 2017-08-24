((t->sparse_list[i].offset +
			       t->sparse_list[i].length) <= 
					t->sparse_list[i+1].offset)
				continue;