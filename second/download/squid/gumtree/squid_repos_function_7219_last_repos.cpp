void
Ipc::Mem::Segment::detach()
{
    if (!theMem)
        return;

    if (munmap(theMem, theSize)) {
        int xerrno = errno;
        debugs(54, 5, "munmap " << theName << ": " << xstrerr(xerrno));
        fatalf("Ipc::Mem::Segment::detach failed to munmap(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));
    }
    theMem = 0;
}