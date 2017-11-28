void ConnStateData::connStateClosed(const CommCloseCbParams &)
{
    deleteThis("ConnStateData::connStateClosed");
}