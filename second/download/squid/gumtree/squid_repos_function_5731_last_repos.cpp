std::vector<Auth::Scheme::Pointer> &
Auth::Scheme::GetSchemes()
{
    if (!_Schemes)
        _Schemes = new std::vector<Auth::Scheme::Pointer>;

    return *_Schemes;
}