    if (ctx < 0 || ctx > CTX_MAX_LEVEL)
        return "<lost>";

    return Ctx_Descrs[ctx] ? Ctx_Descrs[ctx] : "<null>";
}

int Debug::TheDepth = 0;

std::ostream &
Debug::getDebugOut()
{
    assert(TheDepth >= 0);
    ++TheDepth;
    if (TheDepth > 1) {
        assert(CurrentDebug);
        *CurrentDebug << std::endl << "reentrant debuging " << TheDepth << "-{";
    } else {
        assert(!CurrentDebug);
        CurrentDebug = new std::ostringstream();
        // set default formatting flags
        CurrentDebug->setf(std::ios::fixed);
        CurrentDebug->precision(2);
    }
    return *CurrentDebug;
}

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

// Hack: replaces global ::xassert() to debug debugging assertions
// Relies on assert macro calling xassert() without a specific scope.
void
Debug::xassert(const char *msg, const char *file, int line)
{

    if (CurrentDebug) {
        *CurrentDebug << "assertion failed: " << file << ":" << line <<
        ": \"" << msg << "\"";
    }
    abort();
}

std::ostringstream (*Debug::CurrentDebug)(NULL);

size_t
BuildPrefixInit()
{
    // XXX: This must be kept in sync with the actual debug.cc location
    const char *ThisFileNameTail = "src/debug.cc";
