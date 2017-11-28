void Adaptation::DetachServices()
{
    while (!AllServices().empty()) {
        AllServices().back()->detach();
        AllServices().pop_back();
    }
}