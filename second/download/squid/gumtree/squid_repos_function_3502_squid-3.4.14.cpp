void
ClientSocketContext::wroteControlMsg(const Comm::ConnectionPointer &conn, char *, size_t, comm_err_t errflag, int xerrno)
{
    if (errflag == COMM_ERR_CLOSING)
        return;

    if (errflag == COMM_OK) {
        ScheduleCallHere(cbControlMsgSent);
        return;
    }

    debugs(33, 3, HERE << "1xx writing failed: " << xstrerr(xerrno));
    // no error notification: see HttpControlMsg.h for rationale and
    // note that some errors are detected elsewhere (e.g., close handler)

    // close on 1xx errors to be conservative and to simplify the code
    // (if we do not close, we must notify the source of a failure!)
    conn->close();
}