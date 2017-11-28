        if (S_ISDIR(st.st_mode)) {
            debugs(47, (should_exist ? 3 : 1), aPath << " exists");
        } else {
            fatalf("Swap directory %s is not a directory.", aPath);
        }

#ifdef _SQUID_MSWIN_

    } else if (0 == mkdir(aPath)) {
#else

    } else if (0 == mkdir(aPath, 0755)) {
#endif
