MemPools &
MemPools::GetInstance()
{
    // We must initialize on first use (which may happen during static
    // initialization) and preserve until the last user is gone (which
    // may happen long after main() exit). We currently preserve forever.
    static MemPools *Instance = new MemPools;
    return *Instance;
}