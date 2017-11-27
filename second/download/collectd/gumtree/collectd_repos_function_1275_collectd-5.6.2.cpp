static void marshal_ident(const value_list_t *vl, collectd::types::Identifier *msg)
{
	msg->set_host(vl->host);
	msg->set_plugin(vl->plugin);
	if (vl->plugin_instance[0] != '\0')
		msg->set_plugin_instance(vl->plugin_instance);
	msg->set_type(vl->type);
	if (vl->type_instance[0] != '\0')
		msg->set_type_instance(vl->type_instance);
}