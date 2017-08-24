{
			p = tar->sparse_list;
			tar->sparse_list = p->next;
			free(p);
		}