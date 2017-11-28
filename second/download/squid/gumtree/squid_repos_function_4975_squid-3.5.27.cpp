void
Acl::InnerNode::prepareForUse()
{
    std::for_each(nodes.begin(), nodes.end(), std::mem_fun(&ACL::prepareForUse));
}