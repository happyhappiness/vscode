void
Ftp::Server::noteMoreBodySpaceAvailable(BodyPipe::Pointer)
{
    if (!isOpen()) // if we are closing, nothing to do
        return;

    shovelUploadData();
}