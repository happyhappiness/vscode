fatalf("Ipc::Mem::Segment::detach failed to munmap(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));