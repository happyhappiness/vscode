void
Ip::Address::setEmpty()
{
    memset(&mSocketAddr_, 0, sizeof(mSocketAddr_) );
}