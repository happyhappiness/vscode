static void ap_pad(char *dest, size_t size, char ch)
{
    int i = strlen(dest); /* Leave space for trailing '\0' */
    
    while (i < size-1)
	dest[i++] = ch;

    dest[size-1] = '\0';	/* Guarantee for trailing '\0' */
}