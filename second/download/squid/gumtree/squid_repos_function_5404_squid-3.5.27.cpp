void
Ftp::Relay::forwardError(err_type error, int xerrno)
{
    failed(error, xerrno);
}