        storeAppendPrintf(&e, " READ-ONLY");

    storeAppendPrintf(&e, "\n");

}

namespace Rock
{
RunnerRegistrationEntry(rrAfterConfig, SwapDirRr);
}

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

Rock::SwapDirRr::~SwapDirRr()
{
    for (size_t i = 0; i < owners.size(); ++i)
        delete owners[i];
}
