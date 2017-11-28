void
RFCNB_AName_To_NBName(char *AName, char *NBName)
{
    char c, c1, c2;
    int i;

    for (i = 0; i < 16; i++) {

        c = AName[i];

        c1 = (char) ((c >> 4) + 'A');
        c2 = (char) ((c & 0xF) + 'A');

        NBName[i * 2] = c1;
        NBName[i * 2 + 1] = c2;
    }

    NBName[32] = 0;		/* Put in a null */

}