Vector<Auth::Scheme::Pointer> &
Auth::Scheme::GetSchemes()
{
    if (!_Schemes)
        _Schemes = new Vector<Auth::Scheme::Pointer>;

    return *_Schemes;
}