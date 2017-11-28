Log::TcpLogger *
Log::TcpLogger::StillLogging(Logfile *lf)
{
    if (Pointer *pptr = static_cast<Pointer*>(lf->data))
        return pptr->get(); // may be nil
    return NULL;
}