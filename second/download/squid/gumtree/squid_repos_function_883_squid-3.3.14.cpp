void
commCallCloseHandlers(int fd)
{
    fde *F = &fd_table[fd];
    debugs(5, 5, "commCallCloseHandlers: FD " << fd);

    while (F->closeHandler != NULL) {
        AsyncCall::Pointer call = F->closeHandler;
        F->closeHandler = call->Next();
        call->setNext(NULL);
        // If call is not canceled schedule it for execution else ignore it
        if (!call->canceled()) {
            debugs(5, 5, "commCallCloseHandlers: ch->handler=" << call);
            ScheduleCallHere(call);
        }
    }
}