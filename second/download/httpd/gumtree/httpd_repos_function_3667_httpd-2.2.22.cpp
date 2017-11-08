static int same_drive(const char *path1, const char *path2)
{
    char drive1 = path1[0];
    char drive2 = path2[0];

    if (!drive1 || !drive2 || path1[1] != ':' || path2[1] != ':')
        return FALSE;

    if (drive1 == drive2)
        return TRUE;

    if (drive1 >= 'a' && drive1 <= 'z')
        drive1 += 'A' - 'a';

    if (drive2 >= 'a' && drive2 <= 'z')
        drive2 += 'A' - 'a';

    return (drive1 == drive2);
}