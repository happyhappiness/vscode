void
BasicUser::queueRequest(AuthUserRequest * auth_user_request, RH * handler, void *data)
{
    BasicAuthQueueNode *node;
    node = static_cast<BasicAuthQueueNode *>(xmalloc(sizeof(BasicAuthQueueNode)));
    assert(node);
    /* save the details */
    node->next = auth_queue;
    auth_queue = node;
    node->auth_user_request = auth_user_request;
    node->handler = handler;
    node->data = cbdataReference(data);
}