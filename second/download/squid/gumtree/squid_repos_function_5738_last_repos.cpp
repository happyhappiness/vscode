void
Auth::Config::done()
{
    delete keyExtras;
    keyExtras = NULL;
    keyExtrasLine.clean();
}