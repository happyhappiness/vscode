static void release_object_request(struct object_request *obj_req)
{
	if (obj_req->req !=NULL && obj_req->req->localfile != -1)
		error("fd leakage in release: %d", obj_req->req->localfile);

	list_del(&obj_req->node);
	free(obj_req);
}