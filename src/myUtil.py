#-*-coding: utf-8 -*-
import similarity_func
import cluster_control
import analyze_control
import analyze_control_old_new
import csv
from itertools import islice


"""
@ involve : constant definition
"""
USER = 'Kitware'
REPOS = 'CMake'

LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_func_similarity.csv'
FETCH_HUNK_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_hunk_fetch.csv'
FETCH_LOG_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_log_fetch.csv'
ANALYZE_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_analyze.csv'
ANALYZE_REPOS_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_repos_analyze.csv'
ANALYZE_CLONE_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_seek_clone.csv'
STATISTICS_CLONE_NUM_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_clone_statistics.csv'
STATISTICS_OLD_NEW_FILE_NAME = 'data/fetch/' + USER + '_' + REPOS + '_old_new_statistics.csv'

FETCH_HUNK_TITLE = ['hunk', 'flag', 'logs', 'old_hunk_loc', 'new_hunk_loc']
FETCH_HUNK_HUNK = FETCH_HUNK_TITLE.index('hunk')
FETCH_HUNK_FLAG = FETCH_HUNK_TITLE.index('flag')
FETCH_HUNK_LOGS = FETCH_HUNK_TITLE.index('logs')
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')

FETCH_LOG_TITLE = ['commit_sha', 'commit_message', 'file_name', 'change_type', \
                'log_statement', 'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name']
FETCH_LOG_CHANGE_TYPE = FETCH_LOG_TITLE.index('change_type')
FETCH_LOG_LOG = FETCH_LOG_TITLE.index('log_statement')
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_log_loc')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_store_name')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_log_loc')
FETCH_LOG_NEW_FILE = FETCH_LOG_TITLE.index('new_store_name')

ANALYZE_OLD_NEW_TITLE = ['commit_sha', 'commit_message', 'file_name', \
        'change_type', 'log_node', \
        'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name', \
        'old_context_list', 'new_context_list', 'old_ddg_list', 'old_static_list', \
        'new_ddg_list', 'new_static_list']
ANALYZE_OLD_NEW_OLD_CONTEXT = ANALYZE_OLD_NEW_TITLE.index('old_context_list')
ANALYZE_OLD_NEW_NEW_CONTEXT = ANALYZE_OLD_NEW_TITLE.index('new_context_list')

ANALYZE_REPOS_TITLE = ['code', 'location', 'file', 'context_list', 'ddg_list', 'static_list']
ANALYZE_REPOS_CONTEXT = ANALYZE_REPOS_TITLE.index('context_list')

ANALYZE_CLONE_TITLE = ['commit_sha', 'commit_message', 'file_name',\
        'change_type', 'log_node', \
        'old_log_loc', 'old_store_name', 'new_log_loc', 'new_store_name', \
        'old_context_list', 'new_context_list', 'old_ddg_list', 'old_static_list', \
        'new_ddg_list', 'new_static_list', \
        'clone_log', 'clone_location', 'clone_file_name', 'clone_context_list',\
        'clone_ddg_list', 'clone_static_list']

FLAG_LOG_DELETE = -2
FLAG_DELETE = -1
FLAG_NO_CHANGE = 0
FLAG_ADD = 1
FLAG_LOG_ADD = 2

LOG_ADD = 0
LOG_DELETE = 1
LOG_MOVE = 2
LOG_MODIFY = 3

"""
@ param  var to deal with
@ return list of analyzed node info
@ callee ...
@ caller analyze_control.py, similarity_func.py ..
@ involve remove namespace bafore ::,
          and remove caller before ->, .
          and remove parameter after (
"""
def removeNamespace(name):
    # remove namespace before ::
    startpos = name.find("::")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find("::")

    # remove caller before ->
    startpos = name.find("->")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find("->")

    # remove caller before .
    startpos = name.find(".")
    while startpos != -1:
        name = name[startpos + 2:]
        startpos = name.find(".")

    # # remove param after (
    # startpos = name.find("(")
    # while startpos != -1:
    #     name = name[:startpos]
    #     startpos = name.find("(")
    # name = name.strip()

    return name


"""
@ param  element and in_list
@ return in_list
@ callee ...
@ caller cluster_control
@ involve remove given element in in_list
"""
def removeGivenElement(element, in_list):
    # remove element in in_list
    while element in in_list:
        in_list.remove(element)

    return in_list

"""
@ param  isFromRead
@ return function_similarity_dic
@ callee similarity_func.getFunctionSimilarity
@ caller cluster_context_with_function
@ involve call similarity_func.getFunctionSimilarity to get similarity_dic between functions
"""
def getFunctionSimilarityDic(isFromRead):

    func_similarity_dic = {}
    if isFromRead:
        # initialize func_similarity_dict
        analyze_func = file(FUNC_SIMILAIRTY_FILE_NAME, 'rb')
        func_records = csv.reader(analyze_func)
        for func_record in islice(func_records, 1, None):
            func_similarity_dic[(func_record[0], func_record[1])] = func_record[2]
        analyze_func.close()
    else:
        func_similarity_dic = similarity_func.getFunctionSimilarity()
    return func_similarity_dic

"""
@ param  log id and joern instance
@ return cdg_list, neighbor_list, context_list, ddg_list, static_list
@ callee analyze_control.getContextOfLog
@ caller cluster_context_with_function
@ involve get context infomation of given log id
"""
def getContextInfo(log_id, joern_instance):

    cdg_list, neighbor_list, context_list, ddg_node,\
         ddg_list, static_list = analyze_control.getContextOfLog(str(log_id), joern_instance)
    return cdg_list, neighbor_list, context_list, ddg_list, static_list

"""
@ param  similarity_dic, filename
@ return ...
@ callee ...
@ caller self, cluster_context_with_function
@ involve dump similarity_dic into given fileName
"""
def dumpSimilarityDic(similarity_dic, fileName):

    similarity_control = file(fileName, 'wb')
    similarity_control_writer = csv.writer(similarity_control)
    similarity_control_writer.writerow(["left", "right", "similarity"])
    # dump similarity
    for pair, similarity in similarity_dic.items():
        if pair[0] >= 0 and pair[1] >= 0:
            similarity_control_writer.writerow([pair[0], pair[1], similarity])

    # close files
    similarity_control.close()

"""
@ param  context_lists, func_similarity_dic, cluster_similarity
@ return cluster_lists
@ callee cluster_control.cluster_record
@ caller cluster_context_with_function
@ involve cluster the context_lists according to cluster_similarity
"""
def performCluster(context_lists, func_similarity_dic, cluster_similarity, fileName):

    cluster_lists, similarity_dic = cluster_control.cluster_record(context_lists, func_similarity_dic, cluster_similarity)
    dumpSimilarityDic(similarity_dic, fileName)

    return cluster_lists


"""
@ param  dict, key_index
@ return dict
@ callee ...
@ caller cluster_control.computeSim
@ involve remove key contains key_a or key_b specified key_index
"""
def removeDicElement(dictionary, key_index):

    key_list = dictionary.keys()
    key_a = key_list[key_index][0]
    key_b = key_list[key_index][1]
    for key in key_list:
        # if key contains key_a or key_b
        if key[0] == key_a or key[1] == key_b:
            del dictionary[key]

    return dictionary


"""
@ param ...
@ return log_functions
@ caller cluster_context_with_function
@ callee ...
@ involve retrieve log function name from given file
"""
def retrieveLogFunction(fileName):
    log_functions = []
    log_statement = open(fileName, 'rb')
    lines = log_statement.readlines()

    for line in lines:
        log_function = line[0:line.find("@")]
        if not log_function in log_functions:
            log_functions.append(log_function)

    log_statement.close()
    return log_functions

"""
@ param log functions
@ return regrex_string e.g. 'assert|log|debug|print|write|error'
@ caller fetch
@ callee ...
@ involve concate log functions into regrex string
"""
def functionToRegrexStr(log_functions):
    regrex_string = ''
    for log_function in log_functions:
        regrex_string += log_function + '|'

    return regrex_string[:-1]


"""
@ param log id and joernInstance
@ return context list
@ caller analyze_control_repos
@ callee analyze_control_old_new, analyze_control_old_new
@ involve get context info with given log id and joern_instance
"""
def getContext(log_id, joern_instance):
    context_list = []
    order = str(3)
    # condition node list (control type, id, isCFGNode, type, code)
    cdg_query = '_().getCFGControlByLog(' + log_id + ',' + order +')'
    cdg_list = joern_instance.runGremlinQuery(cdg_query)[0] # true/false + cond_node
    # deal with each condition
    for condition in cdg_list:
        context_list = analyze_control_old_new.getCondList(condition, context_list, joern_instance)

    # add flowlabel to make sure the total context count is at least 5
    # context = control + neighbor
    # if len(cdg_list) < 1:
    if len(cdg_list) < 1:
        neighbor_query = '_().getCFGStatementByLog(' + log_id + ',' + order +')'
        neighbor_list = joern_instance.runGremlinQuery(neighbor_query)[0] #  + cond_node
        # deal with each neighbor
        for neighbor in neighbor_list:
            context_list = analyze_control_old_new.getNeighborList(neighbor, context_list, joern_instance)

    return context_list

"""
@ param log id and joernInstance
@ return ddg list and static list
@ caller analyze_control_repos, analyze_control_old_new
@ callee analyze_control_old_new
@ involve get context info with given log id and joern_instance
"""
def getDDGAndContent(log_id, joern_instance):
    ddg_list = []
    static_list = []
    ddg_query = '_().getDDG(' + log_id + ')'
    ddg_node = joern_instance.runGremlinQuery(ddg_query)[0]
    # deal with each ddg_node to get ddg_lists
    for ddg_node in ddg_node:
        ddg_list = analyze_control_old_new.getDDGList(ddg_node, ddg_list, joern_instance)

    # get static string
    static_query = '_().getStaticStr(' + log_id + ')'
    static_list = joern_instance.runGremlinQuery(static_query)[0]

    return ddg_list, static_list

"""
@ param  cond_list of a and b to compute, func_similarity_dic
@ return lenth of common substring / min length
@ callee ...
@ caller compute_context_similarity ..
@ involve compute the longgest common string (continuous) of two cond_list
"""
def longestCommon(list_a, list_b):

    # if just one element, then compare that
    len_a = len(list_a)
    len_b = len(list_b)
    if len_a == 0 or len_b == 0:
        if (len_a + len_b) == 0:
            return float(1)
        else:
            return float(0)
    # length of a and b
    len_a += 1
    len_b += 1

    # find first common and build the common matrix(a*b)
    memory = [[0 for col in range(len_b)] for row in range(len_a)]
    index_a = 0
    index_b = 0
    first_len_common = 0
    for i in range(1, len_a):
        for j in range(1, len_b):
            # update len_common with history
            if list_a[i - 1] == list_b[j-1]:
                memory[i][j] = memory[i-1][j-1] + 1
                if first_len_common < memory[i][j]:
                    first_len_common = memory[i][j]
                    index_a = i
                    index_b = j
                continue
            else:
                memory[i][j] = 0

    len_common = first_len_common
    # filter the totally different and equal condition
    if len_common in range(1, min(len_a, len_b)):
        curr_a = 0
        curr_b = 0
        # find all common in road decide by index_a, index_b
        # forward [1, index_a - 1]
        for i in range(1, min(index_a, index_b)):
            # last common <-- element behind is 0
            curr_a = index_a - i
            curr_b = index_b - i
            if memory[curr_a][curr_b] > 0 and memory[curr_a + 1][curr_b + 1] == 0:
                len_common += memory[curr_a][curr_b]

        # backward [index_a + 1, len_a - 1]
        for i in range(1, min(len_a - index_a, len_b - index_b)):
            # last common <-- element behind is 0
            curr_a = index_a + i
            curr_b = index_b + i
            if memory[curr_a][curr_b] > 0 and \
                (curr_a == len_a - 1 or curr_b == len_b - 1 or memory[curr_a + 1][curr_b + 1] == 0):
                len_common += memory[curr_a][curr_b]

    # simlarity value with common length / min length (0, 1)
    # return float(len_common)/min(len_a, len_b)
    return  len_common



# list_a = [[["chroot", "char [ MAX_STRING_LENGTH + 1 ]"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
# list_b = [[["chroot", "char *"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
# cluster_control.computeSim(list_a, list_b, {})