void
Debug::finishDebug()
{
    assert(TheDepth >= 0);
    assert(CurrentDebug);
    if (TheDepth > 1) {
        *CurrentDebug << "}-" << TheDepth << std::endl;
    } else {
        assert(TheDepth == 1);
        _db_print("%s\n", CurrentDebug->str().c_str());
        delete CurrentDebug;
        CurrentDebug = NULL;
    }
    --TheDepth;
}