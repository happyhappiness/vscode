int
ConnStateData::connReadWasError(comm_err_t flag, int size, int xerrno)
{
    if (flag != COMM_OK) {
        debugs(33, 2, "connReadWasError: FD " << fd << ": got flag " << flag);
        return 1;
    }

    if (size < 0) {
        if (!ignoreErrno(xerrno)) {
            debugs(33, 2, "connReadWasError: FD " << fd << ": " << xstrerr(xerrno));
            return 1;
        } else if (in.notYetUsed == 0) {
            debugs(33, 2, "connReadWasError: FD " << fd << ": no data to process (" << xstrerr(xerrno) << ")");
        }
    }

    return 0;
}