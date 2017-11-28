void
RFCNB_CvtPad_Name(char *name1, char *name2)
{
    char c, c1, c2;
    int i, len;

    len = strlen(name1);

    for (i = 0; i < 16; i++) {

        if (i >= len) {

            c1 = 'C';
            c2 = 'A';		/* CA is a space */

        } else {

            c = name1[i];
            c1 = (char) ((int) c / 16 + (int) 'A');
            c2 = (char) ((int) c % 16 + (int) 'A');
        }

        name2[i * 2] = c1;
        name2[i * 2 + 1] = c2;

    }

    name2[32] = 0;		/* Put in the nll ... */

}