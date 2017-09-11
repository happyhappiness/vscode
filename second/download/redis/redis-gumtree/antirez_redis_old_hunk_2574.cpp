    }

    /* An extra key has changed when ele was successfully added to dstset */
    if (setTypeAdd(dstset,ele)) server.dirty++;
    addReply(c,shared.cone);
}

