bool
HttpRequest::bodyNibbled() const
{
    return body_pipe != NULL && body_pipe->consumedSize() > 0;
}