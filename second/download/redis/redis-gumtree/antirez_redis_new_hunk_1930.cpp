    if (!tokens) return;
    while(count--)
        sdsfree(tokens[count]);
    zfree(tokens);
}

/* Append to the sds string "s" an escaped string representation where
