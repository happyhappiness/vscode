void Adaptation::DetachServices()
{
    while (!AllServices().empty())
        AllServices().pop_back()->detach();
}