            fatalf("Swap directory %s is not a directory.", aPath);
        }
    } else if (0 == mkdir(aPath, 0755)) {
        debugs(47, (should_exist ? DBG_IMPORTANT : 3), aPath << " created");
        created = 1;
    } else {
        int xerrno = errno;
        fatalf("Failed to make swap directory %s: %s", aPath, xstrerr(xerrno));
    }

    return created;
}

bool
Fs::Ufs::UFSSwapDir::pathIsDirectory(const char *aPath)const
{

    struct stat sb;

    if (::stat(aPath, &sb) < 0) {
        int xerrno = errno;
        debugs(47, DBG_CRITICAL, "ERROR: " << aPath << ": " << xstrerr(xerrno));
        return false;
    }

    if (S_ISDIR(sb.st_mode) == 0) {
        debugs(47, DBG_CRITICAL, "WARNING: " << aPath << " is not a directory");
        return false;
