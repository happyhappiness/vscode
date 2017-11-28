static void
random_vector(char *aVector)
{
    int randno;
    int i;

    srand((time(0) ^ rand()) + rand());
    for (i = 0; i < AUTH_VECTOR_LEN;) {
        randno = rand();
        memcpy(aVector, &randno, sizeof(int));
        aVector += sizeof(int);
        i += sizeof(int);
    }
}