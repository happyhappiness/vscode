void** dlindependent_calloc(size_t n_elements, size_t elem_size,
				 void* chunks[]) {
  size_t sz = elem_size; /* serves as 1-element array */
  return ialloc(gm, n_elements, &sz, 3, chunks);
}