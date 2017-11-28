void
Adaptation::Config::FreeAccess()
{
    while (!AllRules().empty()) {
        delete AllRules().back();
        AllRules().pop_back();
    }
}