fatalf("shared_memory_locking on but failed to mlock(%s, %" PRId64 "): %s\n",
               theName.termedBuf(),static_cast<int64_t>(theSize), xstrerr(savedError));