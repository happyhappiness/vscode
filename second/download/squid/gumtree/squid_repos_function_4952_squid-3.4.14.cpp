void
Rock::IoState::close(int how)
{
    debugs(79, 3, HERE << swap_filen << " accumulated: " << offset_ <<
           " how=" << how);
    if (how == wroteAll && !theBuf.isNull())
        startWriting();
    else
        callBack(how == writerGone ? DISK_ERROR : 0); // TODO: add DISK_CALLER_GONE
}