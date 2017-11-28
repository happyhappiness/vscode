Ipc::StrandCoords
Mgr::Inquirer::applyQueryParams(const Ipc::StrandCoords& aStrands, const QueryParams& aParams)
{
    Ipc::StrandCoords sc;

    QueryParam::Pointer processesParam = aParams.get("processes");
    QueryParam::Pointer workersParam = aParams.get("workers");

    if (processesParam == NULL || workersParam == NULL) {
        if (processesParam != NULL) {
            IntParam* param = dynamic_cast<IntParam*>(processesParam.getRaw());
            if (param != NULL && param->type == QueryParam::ptInt) {
                const std::vector<int>& processes = param->value();
                for (Ipc::StrandCoords::const_iterator iter = aStrands.begin();
                        iter != aStrands.end(); ++iter) {
                    if (std::find(processes.begin(), processes.end(), iter->kidId) != processes.end())
                        sc.push_back(*iter);
                }
            }
        } else if (workersParam != NULL) {
            IntParam* param = dynamic_cast<IntParam*>(workersParam.getRaw());
            if (param != NULL && param->type == QueryParam::ptInt) {
                const std::vector<int>& workers = param->value();
                for (int i = 0; i < (int)aStrands.size(); ++i) {
                    if (std::find(workers.begin(), workers.end(), i + 1) != workers.end())
                        sc.push_back(aStrands[i]);
                }
            }
        } else {
            sc = aStrands;
        }
    }

    debugs(16, 4, HERE << "strands kid IDs = ");
    for (Ipc::StrandCoords::const_iterator iter = sc.begin(); iter != sc.end(); ++iter) {
        debugs(16, 4, HERE << iter->kidId);
    }

    return sc;
}