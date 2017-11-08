int main(void)
{
    fprintf(stderr,
            "This program won't work on this platform because there is no "
            "support for sendfile().\n");
    return 0;
}