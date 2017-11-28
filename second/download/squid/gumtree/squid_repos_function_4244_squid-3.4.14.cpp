void Adaptation::Icap::OptXact::handleCommWrote(size_t size)
{
    debugs(93, 9, HERE << "finished writing " << size <<
           "-byte request " << status());
}