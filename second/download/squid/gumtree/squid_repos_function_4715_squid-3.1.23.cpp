void
UFSStoreState::tryClosing()
{
    debugs(79,3,HERE << this << " tryClosing()" <<
           " closing = " << closing <<
           " flags.try_closing = " << flags.try_closing <<
           " ioInProgress = " << theFile->ioInProgress());

    if (theFile->ioInProgress()) {
        debugs(79, 3, HERE << this <<
               " won't close since ioInProgress is true, bailing");
        flags.try_closing = true;
        return;
    }

    closing = true;
    flags.try_closing = false;
    theFile->close();
}