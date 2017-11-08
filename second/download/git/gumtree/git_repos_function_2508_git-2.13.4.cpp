static void abort_object_request(struct object_request *obj_req)
{
	release_object_request(obj_req);
}