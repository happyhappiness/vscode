void
Http::One::Server::noteBodyConsumerAborted(BodyPipe::Pointer ptr)
{
    ConnStateData::noteBodyConsumerAborted(ptr);
    stopReceiving("virgin request body consumer aborted"); // closes ASAP
}