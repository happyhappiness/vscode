void Rock::SwapDirRr::create(const RunnerRegistry &)
{
    Must(owners.empty());
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        if (const Rock::SwapDir *const sd = dynamic_cast<Rock::SwapDir *>(INDEXSD(i))) {
            Rock::SwapDir::DirMap::Owner *const owner =
                Rock::SwapDir::DirMap::Init(sd->path, sd->entryLimitAllowed());
            owners.push_back(owner);
        }
    }
}