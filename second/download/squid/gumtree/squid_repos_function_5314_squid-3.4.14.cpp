const char *
Auth::Basic::Config::type() const
{
    return Auth::Basic::Scheme::GetInstance()->type();
}