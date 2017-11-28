void
ServerStateData::noteMoreBodySpaceAvailable(BodyPipe::Pointer)
{
    if (responseBodyBuffer) {
        addVirginReplyBody(NULL, 0); // kick the buffered fragment alive again
        if (completed && !responseBodyBuffer) {
            serverComplete2();
            return;
        }
    }
    maybeReadVirginBody();
}