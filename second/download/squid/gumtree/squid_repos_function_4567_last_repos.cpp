StoreSearch *
Store::Controller::search()
{
    // this is the only kind of search we currently support
    return NewLocalSearch();
}