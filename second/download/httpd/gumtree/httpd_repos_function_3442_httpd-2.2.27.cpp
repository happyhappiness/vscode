int main(void)
{
    char buf[256];
    int bytes;
    
    bytes = (int)read(STDIN_FILENO, buf, 256);
    if (bytes > 0)
        write(STDOUT_FILENO, buf, (unsigned int)bytes);

    return 0; /* just to keep the compiler happy */
}