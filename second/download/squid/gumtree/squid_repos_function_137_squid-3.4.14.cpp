void
SplayCheck::CheckNode(intnode const &A)
{
    if (LastValue > A.i) {
        /* failure */

        if (!ExpectedFail)
            exit (1);
    } else
        /* success */
        if (ExpectedFail)
            exit (1);

    LastValue = A.i;
}