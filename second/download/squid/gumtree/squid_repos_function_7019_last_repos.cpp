void Ipc::AssertFlagIsSet(std::atomic_flag &flag)
{
    // If the flag was false, then we set it to true and assert. A true flag
    // may help keep other processes away from this broken entry.
    // Otherwise, we just set an already set flag, which is probably a no-op.
    assert(flag.test_and_set(std::memory_order_relaxed));
}