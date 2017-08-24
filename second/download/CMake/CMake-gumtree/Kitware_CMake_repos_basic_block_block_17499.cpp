{
		next_heap = heap->next;
		free(heap);
		heap = next_heap;
	}