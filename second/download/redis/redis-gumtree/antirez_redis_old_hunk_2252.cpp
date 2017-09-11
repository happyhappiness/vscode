    if (val) listAddNodeTail(keys, val);
}

/* This command implements SCAN, HSCAN and SSCAN commands.
 * If object 'o' is passed, then it must be an Hash or Set object, otherwise
 * if 'o' is NULL the command will operate on the dictionary associated with
