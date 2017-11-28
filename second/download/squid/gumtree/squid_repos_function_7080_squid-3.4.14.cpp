inline int
pipe(int pipefd[2])
{
    return _pipe(pipefd,4096,_O_BINARY);
}