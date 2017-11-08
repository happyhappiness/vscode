static int isSecureUpgraded (const request_rec *r)
{
    secsocket_data *csd_data = (secsocket_data*)ap_get_module_config(r->connection->conn_config, &nwssl_module);

	return csd_data->is_secure;
}