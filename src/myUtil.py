#-*-coding: utf-8 -*-
import csv
import commands
import os
from itertools import islice
import numpy as np
from scipy.spatial.distance import pdist
import similarity_func
import my_constant

"""
@ param  var to deal with
@ return list of analyzed node info
@ involve remove namespace bafore ::,
          and remove caller before ->, .
          and remove parameter after (
"""
def remove_name_space_and_caller(name):
    # remove namespace before ::
    startpos = name.find("::")
    while not startpos == -1:
        name = name[startpos + 2:]
        startpos = name.find("::")

    # remove caller before ->
    startpos = name.find("->")
    while not startpos == -1:
        name = name[startpos + 2:]
        startpos = name.find("->")

    # remove caller before .
    startpos = name.find(".")
    while not startpos == -1:
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
@ involve remove given element in in_list
"""
def remove_given_element(element, in_list):
    # remove element in in_list
    while element in in_list:
        in_list.remove(element)

    return in_list


"""
@ param  list
@ return dictionary
@ callee ...
@ caller block
@ involve transform list into dict
"""
def dict_from_list(in_list):
    len_list = len(in_list)
    out_dict = {}
    for i in range(len_list):
        out_dict[in_list[i]] = i

    return out_dict

"""
@ param  isFromRead
@ return function_similarity_dic
@ involve call similarity_func.getFunctionSimilarity to get similarity_dic between functions
"""
def getFunctionSimilarityDic(isFromRead):

    func_similarity_dic = {}
    if isFromRead:
        # initialize func_similarity_dict
        analyze_func = file(my_constant.FUNC_SIMILAIRTY_FILE_NAME, 'rb')
        func_records = csv.reader(analyze_func)
        for func_record in islice(func_records, 1, None):
            func_similarity_dic[(func_record[0], func_record[1])] = func_record[2]
        analyze_func.close()
    else:
        func_similarity_dic = similarity_func.getFunctionSimilarity()
    return func_similarity_dic

"""
@ param  similarity_dic, filename
@ return ...
@ callee ...
@ caller self, cluster_context_with_function
@ involve dump similarity_dic
"""
def dumpSimilarityDic(similarity_dic):

    similarity_control = file(my_constant.REPOS_SIMILARITY_FILE_NAME, 'wb')
    similarity_control_writer = csv.writer(similarity_control)
    similarity_control_writer.writerow(["left", "right", "similarity"])
    # dump similarity
    for pair, similarity in similarity_dic.items():
        if pair[0] >= 0 and pair[1] >= 0:
            similarity_control_writer.writerow([pair[0], pair[1], similarity])

    # close files
    similarity_control.close()


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
@ return delta_set
@ caller fetch
@ callee ...
@ involve calculate (A U B) - (A J B)[occurrence diff]
"""
def get_delta_of_two_set(set_a, set_b):
    union_set = set_a.union(set_b)
    join_set = set_a.intersection(set_b)
    delta_set = union_set.difference(join_set)
    return delta_set

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
@ return regrex_string e.g. '[assert|log|debug|print|write|error]('
@ involve concate log functions into regrex string
"""
def functionToRegrexStr(log_functions):
    regrex_string = r'\W('
    for log_function in log_functions:
        regrex_string += log_function + r'|'
    regrex_string = regrex_string[:-1]
    regrex_string += r')(\s*\(.*|\s*$)'

    return regrex_string

"""
@ param vactors to compare
@ return similarity
@ involve compute cos similarity of two vectors
"""
def compute_similarity(in_vector1, in_vector2, method='braycurtis'):
    # multi = np.sum(np.multiply(in_vector1, in_vector2))
    # base = (np.linalg.norm(in_vector1) * np.linalg.norm(in_vector1))
    # if base > 0:
    #     similairy = float(multi) / base
    # else:
    #     return np.sum(in_vector1 + in_vector2) == 0
    # return similairy
    if in_vector1 == [] or in_vector2 == []:
        return 1.0
    # print in_vector1
    # print in_vector2
    X = np.vstack([in_vector1, in_vector2])
    # standard distance
    distance = pdist(X, metric=method)
    similairty = 1 - distance
    return similairty

"""
@ param filename and file content
@ return
@ involve save file content into given file
"""
def save_file(content, file_name):
    write_file = open(file_name, 'wb')
    write_file.write(content)
    write_file.close()


"""
@ param old file name and new file name
@ return
@ involve copy file from old file to new file
"""
def copy_file(old_file_name, new_file_name):
    read_file = open(old_file_name, 'rb')
    content = read_file.read()
    write_file = open(new_file_name, 'wb')
    write_file.write(content)
    read_file.close()
    write_file.close()

"""
@ param joernIndex parent dir
@ return
@ involve rm old joernIndex file, and build new one. restart neo4j server
"""
def rebuild_joern_index(index_dir, code_dir):
    output = commands.getoutput('rm -r ' + index_dir)
    output = commands.getoutput('java -Xmx4g -Xms4g -jar $JOERN/bin/joern.jar ' + code_dir + ' -outdir ' + index_dir)
    output = commands.getoutput('neo4j restart')
    print output

"""
@ param list of tuple
@ return tuple
@ involve switch list of tuple to tuple
"""
def get_tuple_from_list(tuple_list):
    tuple_tuple = ()
    for tuple_element in tuple_list:
        tuple_tuple += tuple(tuple_element)
    return tuple_tuple

"""
@ param list of a and b to compute
@ return lenth of common substring / min length
@ involve compute the longgest common string (continuous) of two list
"""
def longest_common_sub(list_a, list_b):

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
    # filter the totally different and equal
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

    return  len_common



# list_a = [[["chroot", "char [ MAX_STRING_LENGTH + 1 ]"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
# list_b = [[["chroot", "char *"]], [["!", "strcasecmp", "config_getoption", "\"DO_CHROOT\"", "\"yes\""]], [["!", "char *", "0"]], [["int"]], [["!", "char *", "0"]], [["!", "int"]]]
# cluster_control.computeSim(list_a, list_b, {})