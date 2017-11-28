void
ConnStateData::sendControlMsg(HttpControlMsg msg)
{
    if (!isOpen()) {
        debugs(33, 3, HERE << "ignoring 1xx due to earlier closure");
        return;
    }

    ClientSocketContext::Pointer context = getCurrentContext();
    if (context != NULL) {
        context->writeControlMsg(msg); // will call msg.cbSuccess
        return;
    }

    debugs(33, 3, HERE << " closing due to missing context for 1xx");
    clientConnection->close();
}