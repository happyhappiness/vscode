static void finish_object_request(struct object_request *obj_req)
{
	if (finish_http_object_request(obj_req->req))
		return;

	if (obj_req->req->rename == 0)
		walker_say(obj_req->walker, "got %s\n", sha1_to_hex(obj_req->sha1));
}