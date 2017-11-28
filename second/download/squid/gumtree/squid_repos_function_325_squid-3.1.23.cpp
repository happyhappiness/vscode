void
RFCNB_NBName_To_AName(char *NBName, char *AName)
{
    char c, c1, c2;
    int i;

    for (i = 0; i < 16; i++) {

        c1 = NBName[i * 2];
        c2 = NBName[i * 2 + 1];

        c = (char) (((int) c1 - (int) 'A') * 16 + ((int) c2 - (int) 'A'));

        AName[i] = c;

    }

    AName[i] = 0;		/* Put a null on the end ... */

}