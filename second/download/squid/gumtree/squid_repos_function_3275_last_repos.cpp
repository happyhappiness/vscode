Adaptation::AccessRules &
Adaptation::AllRules()
{
    static AccessRules *TheRules = new AccessRules;
    return *TheRules;
}