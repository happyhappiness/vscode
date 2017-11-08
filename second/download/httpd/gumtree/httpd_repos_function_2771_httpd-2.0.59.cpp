int main(void)
{
    char buf[256];
    apr_ssize_t bytes;
    
    bytes = read(STDIN_FILENO, buf, 256);
    if (bytes > 0)
        write(STDOUT_FILENO, buf, bytes);

    return 0; /* just to keep the compiler happy */
}