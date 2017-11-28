bool
Fs::Ufs::UFSSwapDir::FilenoBelongsHere(int fn, int F0, int F1, int F2)
{
    int D1, D2;
    int L1, L2;
    int filn = fn;
    assert(F0 < Config.cacheSwap.n_configured);
    assert (UFSSwapDir::IsUFSDir (dynamic_cast<SwapDir *>(INDEXSD(F0))));
    UFSSwapDir *sd = dynamic_cast<UFSSwapDir *>(INDEXSD(F0));

    if (!sd)
        return 0;

    L1 = sd->l1;

    L2 = sd->l2;

    D1 = ((filn / L2) / L2) % L1;

    if (F1 != D1)
        return 0;

    D2 = (filn / L2) % L2;

    if (F2 != D2)
        return 0;

    return 1;
}