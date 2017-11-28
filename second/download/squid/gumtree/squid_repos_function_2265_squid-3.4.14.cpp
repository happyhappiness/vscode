void
ServerStateData::doneSendingRequestBody()
{
    debugs(9,3, HERE << "done sending request body");
    assert(requestBodySource != NULL);
    stopConsumingFrom(requestBodySource);

    // kids extend this
}