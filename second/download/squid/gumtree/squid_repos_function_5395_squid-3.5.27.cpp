void
Ftp::Relay::failed(err_type error, int xerrno, ErrorState *ftpErr)
{
    if (!doneWithServer())
        serverState(fssError);

    // TODO: we need to customize ErrorState instead
    if (entry->isEmpty())
        failedErrorMessage(error, xerrno); // as a reply

    Ftp::Client::failed(error, xerrno, ftpErr);
}