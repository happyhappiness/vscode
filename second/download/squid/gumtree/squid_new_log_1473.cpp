fatalf("Ipc::Mem::Segment::statSize: %s failed to fstat(%s): %s\n",
               context, theName.termedBuf(), xstrerr(xerrno));