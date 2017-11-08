static FORCEINLINE void* win32direct_mmap(size_t size) {
  void* ptr = VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT|MEM_TOP_DOWN,
			   PAGE_READWRITE);
  return (ptr != 0)? ptr: MFAIL;
}