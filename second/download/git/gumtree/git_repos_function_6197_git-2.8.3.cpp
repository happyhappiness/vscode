void** dlindependent_comalloc(size_t n_elements, size_t sizes[],
				   void* chunks[]) {
  return ialloc(gm, n_elements, sizes, 0, chunks);
}