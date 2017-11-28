void
DeferredReadManager::CloseHandler(const CommCloseCbParams &params)
{
    if (!cbdataReferenceValid(params.data))
        return;

    CbDataList<DeferredRead> *temp = (CbDataList<DeferredRead> *)params.data;

    temp->element.closer = NULL;
    temp->element.markCancelled();
}