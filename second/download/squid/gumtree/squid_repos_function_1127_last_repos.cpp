void
Downloader::CbDialer::print(std::ostream &os) const
{
    os << " Http Status:" << status << Raw("body data", object.rawContent(), 64).hex();
}