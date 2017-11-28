Adaptation::Groups &
Adaptation::AllGroups()
{
    static Groups *TheGroups = new Groups;
    return *TheGroups;
}