const char *
Auth::Negotiate::Config::type() const
{
    return Auth::Negotiate::Scheme::GetInstance()->type();
}