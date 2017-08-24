{
			memcpy(p, heap->reqs, heap->cnt * sizeof(*p));
			free(heap->reqs);
		}