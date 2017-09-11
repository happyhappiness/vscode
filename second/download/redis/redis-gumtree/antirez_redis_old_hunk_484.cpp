                    return;
                }
                i++;
            } else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    /* COUNT without ordering does not make much sense, force ASC
     * ordering if COUNT was specified but no sorting was requested. */
    if (count != 0 && sort == SORT_NONE) sort = SORT_ASC;
