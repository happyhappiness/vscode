void ConnStateData::connStateClosed(const CommCloseCbParams &io)
{
    assert (fd == io.fd);
    deleteThis("ConnStateData::connStateClosed");
}