void
DeferredReadManager::CloseHandler(int fd, void *thecbdata)
{
    if (!cbdataReferenceValid (thecbdata))
        return;

    CbDataList<DeferredRead> *temp = (CbDataList<DeferredRead> *)thecbdata;

    temp->element.closer = NULL;
    temp->element.markCancelled();
}