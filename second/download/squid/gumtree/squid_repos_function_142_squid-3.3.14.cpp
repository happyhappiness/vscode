int
main(int argc, char *argv[])
{
    {
        int i;
        intnode *I;
        /* test void * splay containers */
        splayNode *top = NULL;
        squid_srandom(time(NULL));

        for (i = 0; i < 100; ++i) {
            I = (intnode *)xcalloc(sizeof(intnode), 1);
            I->i = squid_random();
            top = top->insert(I, compareintvoid);
        }

        SplayCheck::BeginWalk();
        top->walk(SplayCheck::WalkVoid, NULL);

        SplayCheck::BeginWalk();
        top->walk(SplayCheck::WalkVoid, NULL);
        top->destroy(destintvoid);
        /* check we don't segfault on NULL splay calls */
        top = NULL;
        top->splay((void *)NULL, compareintvoid);
    }

    /* test typesafe splay containers */
    {
        /* intnode* */
        SplayNode<intnode *> *safeTop = NULL;

        for ( int i = 0; i < 100; ++i) {
            intnode *I;
            I = new intnode;
            I->i = squid_random();
            safeTop = safeTop->insert(I, compareint);
        }

        SplayCheck::BeginWalk();
        safeTop->walk(SplayCheck::WalkNode, NULL);

        safeTop->destroy(destint);
        /* check we don't segfault on NULL splay calls */
        safeTop = NULL;
        safeTop->splay((intnode *)NULL, compareint);
    }
    {
        /* intnode */
        SplayNode<intnode> *safeTop = NULL;

        for (int i = 0; i < 100; ++i) {
            intnode I;
            I.i = squid_random();
            safeTop = safeTop->insert(I, compareintref);
        }

        SplayCheck::BeginWalk();
        safeTop->walk(SplayCheck::WalkNodeRef, NULL);

        safeTop->destroy(destintref);
        /* check we don't segfault on NULL splay calls */
        safeTop = NULL;
        safeTop->splay(intnode(), compareintref);
        SplayCheck::BeginWalk();
        safeTop->walk(SplayCheck::WalkNodeRef, NULL);
    }
    /* check the check routine */
    SplayCheck::BeginWalk();
    intnode I;
    I.i = 1;
    /* check we don't segfault on NULL splay calls */
    SplayCheck::WalkNodeRef(I, NULL);
    I.i = 0;
    SplayCheck::ExpectedFail = true;
    SplayCheck::WalkNodeRef(I, NULL);

    {
        /* check for begin() */
        SplayNode<intnode> *safeTop = NULL;

        if (safeTop->start() != NULL)
            exit (1);

        if (safeTop->finish() != NULL)
            exit (1);

        for (int i = 0; i < 100; ++i) {
            intnode I;
            I.i = squid_random();

            if (I.i > 50 && I.i < 10000000)
                safeTop = safeTop->insert(I, compareintref);
        }

        {
            intnode I;
            I.i = 50;
            safeTop = safeTop->insert (I, compareintref);
            I.i = 10000000;
            safeTop = safeTop->insert (I, compareintref);
        }

        if (!safeTop->start())
            exit (1);

        if (safeTop->start()->data.i != 50)
            exit (1);

        if (!safeTop->finish())
            exit (1);

        if (safeTop->finish()->data.i != 10000000)
            exit (1);

        safeTop->destroy(destintref);
    }

    {
        Splay<intnode *> aSplay;

        if (aSplay.start() != NULL)
            exit (1);

        if (aSplay.size() != 0)
            exit (1);

        aSplay.insert (new intnode(5), compareint);

        if (aSplay.start() == NULL)
            exit (1);

        if (aSplay.size() != 1)
            exit (1);

        aSplay.destroy(destint);

        if (aSplay.start() != NULL)
            exit (1);

        if (aSplay.size() != 0)
            exit (1);
    }

    return 0;
}