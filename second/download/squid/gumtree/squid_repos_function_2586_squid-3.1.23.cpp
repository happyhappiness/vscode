void
FtpStateData::failed(err_type error, int xerrno)
{
    debugs(9,3,HERE << "entry-null=" << (entry?entry->isEmpty():0) << ", entry=" << entry);
    if (entry->isEmpty())
        failedErrorMessage(error, xerrno);

    serverComplete();
}