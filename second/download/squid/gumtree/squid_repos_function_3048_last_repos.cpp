static bool
httpsCreate(const Comm::ConnectionPointer &conn, const Security::ContextPointer &ctx)
{
    if (Security::CreateServerSession(ctx, conn, "client https start")) {
        debugs(33, 5, "will negotiate TLS on " << conn);
        return true;
    }

    conn->close();
    return false;
}