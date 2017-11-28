void
ConnStateData::noteMoreBodySpaceAvailable(BodyPipe::Pointer )
{
    if (!handleRequestBodyData())
        return;

    // too late to read more body
    if (!isOpen() || stoppedReceiving())
        return;

    readSomeData();
}