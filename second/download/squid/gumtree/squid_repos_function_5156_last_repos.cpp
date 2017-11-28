int
Fs::Ufs::UFSSwapDir::DirClean(int swap_index)
{
    DIR *dir_pointer = NULL;

    LOCAL_ARRAY(char, p1, MAXPATHLEN + 1);
    LOCAL_ARRAY(char, p2, MAXPATHLEN + 1);

    int files[20];
    int swapfileno;
    int fn;         /* same as swapfileno, but with dirn bits set */
    int n = 0;
    int k = 0;
    int N0, N1, N2;
    int D0, D1, D2;
    UFSSwapDir *SD;
    N0 = NumberOfUFSDirs;
    D0 = UFSDirToGlobalDirMapping[swap_index % N0];
    SD = dynamic_cast<UFSSwapDir *>(INDEXSD(D0));
    assert (SD);
    N1 = SD->l1;
    D1 = (swap_index / N0) % N1;
    N2 = SD->l2;
    D2 = ((swap_index / N0) / N1) % N2;
    snprintf(p1, MAXPATHLEN, "%s/%02X/%02X",
             SD->path, D1, D2);
    debugs(36, 3, HERE << "Cleaning directory " << p1);
    dir_pointer = opendir(p1);

    if (!dir_pointer) {
        int xerrno = errno;
        if (xerrno == ENOENT) {
            debugs(36, DBG_CRITICAL, MYNAME << "WARNING: Creating " << p1);
            if (mkdir(p1, 0777) == 0)
                return 0;
        }

        debugs(50, DBG_CRITICAL, MYNAME << p1 << ": " << xstrerr(xerrno));
        safeunlink(p1, 1);
        return 0;
    }

    dirent_t *de;
    while ((de = readdir(dir_pointer)) != NULL && k < 20) {
        if (sscanf(de->d_name, "%X", &swapfileno) != 1)
            continue;

        fn = swapfileno;    /* XXX should remove this cruft ! */

        if (SD->validFileno(fn, 1))
            if (SD->mapBitTest(fn))
                if (UFSSwapDir::FilenoBelongsHere(fn, D0, D1, D2))
                    continue;

        files[k] = swapfileno;
        ++k;
    }

    closedir(dir_pointer);

    if (k == 0)
        return 0;

    qsort(files, k, sizeof(int), rev_int_sort);

    if (k > 10)
        k = 10;

    for (n = 0; n < k; ++n) {
        debugs(36, 3, HERE << "Cleaning file "<< std::setfill('0') << std::hex << std::uppercase << std::setw(8) << files[n]);
        snprintf(p2, MAXPATHLEN + 1, "%s/%08X", p1, files[n]);
        safeunlink(p2, 0);
        ++statCounter.swap.files_cleaned;
    }

    debugs(36, 3, HERE << "Cleaned " << k << " unused files from " << p1);
    return k;
}