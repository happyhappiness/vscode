static grpc::Status unmarshal_ident(const collectd::types::Identifier &msg, value_list_t *vl,
		bool require_fields)
{
	std::string s;

	s = msg.host();
	if (!s.length() && require_fields)
		return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
				grpc::string("missing host name"));
	sstrncpy(vl->host, s.c_str(), sizeof(vl->host));

	s = msg.plugin();
	if (!s.length() && require_fields)
		return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
				grpc::string("missing plugin name"));
	sstrncpy(vl->plugin, s.c_str(), sizeof(vl->plugin));

	s = msg.type();
	if (!s.length() && require_fields)
		return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
				grpc::string("missing type name"));
	sstrncpy(vl->type, s.c_str(), sizeof(vl->type));

	s = msg.plugin_instance();
	sstrncpy(vl->plugin_instance, s.c_str(), sizeof(vl->plugin_instance));

	s = msg.type_instance();
	sstrncpy(vl->type_instance, s.c_str(), sizeof(vl->type_instance));

	return grpc::Status::OK;
}