void Adaptation::Icap::ModXact::handleCommRead(size_t)
{
    Must(!state.doneParsing());
    icap_tio_finish = current_time;
    parseMore();
    readMore();
}