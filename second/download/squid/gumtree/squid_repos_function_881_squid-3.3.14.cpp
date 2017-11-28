int
commUnsetConnTimeout(const Comm::ConnectionPointer &conn)
{
    debugs(5, 3, HERE << "Remove timeout for " << conn);
    AsyncCall::Pointer nil;
    return commSetConnTimeout(conn, -1, nil);
}