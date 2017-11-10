static int dav_fs_compare_locktoken(
    const dav_locktoken *lt1,
    const dav_locktoken *lt2)
{
    return dav_compare_locktoken(lt1, lt2);
}