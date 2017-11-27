static void za_submit_derive (const char* type, const char* type_instance, derive_t dv)
{
	value_t vv;

	vv.derive = dv;
	za_submit (type, type_instance, &vv, 1);
}