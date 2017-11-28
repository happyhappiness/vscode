bool
Security::CreateServerSession(const Security::ContextPointer &ctx, const Comm::ConnectionPointer &c, const char *squidCtx)
{
    return CreateSession(ctx, c, Security::Io::BIO_TO_CLIENT, squidCtx);
}