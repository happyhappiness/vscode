void
Ipc::Mem::Segment::unlink()
{
    if (shm_unlink(theName.termedBuf()) != 0) {
        int xerrno = errno;
        debugs(54, 5, "shm_unlink(" << theName << "): " << xstrerr(xerrno));
    } else
        debugs(54, 3, "unlinked " << theName << " segment");
}