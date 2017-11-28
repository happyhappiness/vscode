void
Fs::Ufs::UFSStoreState::freePending()
{
    _queued_read *qr;

    while ((qr = (_queued_read *)linklistShift(&pending_reads))) {
        cbdataReferenceDone(qr->callback_data);
        delete qr;
    }

    debugs(79,3,HERE << "UFSStoreState::freePending: freed pending reads");

    _queued_write *qw;

    while ((qw = (_queued_write *)linklistShift(&pending_writes))) {
        if (qw->free_func)
            qw->free_func(const_cast<char *>(qw->buf));
        delete qw;
    }

    debugs(79,3,HERE << "UFSStoreState::freePending: freed pending writes");
}