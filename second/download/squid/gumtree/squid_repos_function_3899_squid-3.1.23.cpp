void Adaptation::Icap::ModXact::startReading()
{
    Must(connection >= 0);
    Must(!reader);
    Must(!adapted.header);
    Must(!adapted.body_pipe);

    // we use the same buffer for headers and body and then consume headers
    readMore();
}