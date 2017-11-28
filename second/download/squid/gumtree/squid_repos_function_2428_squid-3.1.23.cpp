void
FwdState::serversFree(FwdServer ** FSVR)
{
    FwdServer *fs;

    while ((fs = *FSVR)) {
        *FSVR = fs->next;
        fwdServerFree(fs);
    }
}