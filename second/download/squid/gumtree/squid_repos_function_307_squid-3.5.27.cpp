int
add_User_Group(wchar_t * Group)
{
    wchar_t **array;

    if (User_Groups_Count == 0) {
        User_Groups = (wchar_t **) xmalloc(sizeof(wchar_t *));
        *User_Groups = NULL;
        ++User_Groups_Count;
    }
    array = User_Groups;
    while (*array) {
        if (wcscmp(Group, *array) == 0)
            return 0;
        ++array;
    }
    User_Groups = (wchar_t **) xrealloc(User_Groups, sizeof(wchar_t *) * (User_Groups_Count + 1));
    User_Groups[User_Groups_Count] = NULL;
    User_Groups[User_Groups_Count - 1] = (wchar_t *) xmalloc((wcslen(Group) + 1) * sizeof(wchar_t));
    wcscpy(User_Groups[User_Groups_Count - 1], Group);
    ++User_Groups_Count;

    return 1;
}