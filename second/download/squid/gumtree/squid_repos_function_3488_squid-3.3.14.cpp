void ConnStateData::connStateClosed(const CommCloseCbParams &io)
{
    deleteThis("ConnStateData::connStateClosed");
}