void
Http::Server::noteBodyConsumerAborted(BodyPipe::Pointer ptr)
{
    ConnStateData::noteBodyConsumerAborted(ptr);
    stopReceiving("virgin request body consumer aborted"); // closes ASAP
}