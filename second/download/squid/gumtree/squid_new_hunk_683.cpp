    if (toVisit.size() == 0)
        fatal ("Attempt to dereference SplayConstIterator past-the-end\n");

    return toVisit.top()->data;
}

#endif /* SQUID_SPLAY_H */

