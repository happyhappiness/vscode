void
FwdState::doneWithRetries()
{
    if (request && request->body_pipe != NULL)
        request->body_pipe->expectNoConsumption();
}