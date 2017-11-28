void
Ident::WriteFeedback(const Comm::ConnectionPointer &conn, char *, size_t len, Comm::Flag flag, int xerrno, void *data)
{
    debugs(30, 5, HERE << conn << ": Wrote IDENT request " << len << " bytes.");

    // TODO handle write errors better. retry or abort?
    if (flag != Comm::OK) {
        debugs(30, 2, HERE << conn << " err-flags=" << flag << " IDENT write error: " << xstrerr(xerrno));
        IdentStateData *state = (IdentStateData *)data;
        state->deleteThis("write error");
    }
}