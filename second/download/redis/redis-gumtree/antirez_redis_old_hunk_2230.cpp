        ri = sentinelGetMasterByName(argv[1]);
        if (!ri) return "No such master with specified name.";
        ri->auth_pass = sdsnew(argv[2]);
    } else {
        return "Unrecognized sentinel configuration statement.";
    }
    return NULL;
}

/* ====================== hiredis connection handling ======================= */

/* Completely disconnect an hiredis link from an instance. */
