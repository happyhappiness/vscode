#-*-coding: utf-8 -*-
import csv
import commands
import re
from itertools import islice
import numpy as np
from scipy.spatial.distance import pdist
import similarity_func
import my_constant

def remove_name_space_and_caller(name):
    """
    @ param variable name\n
    @ return new variable name\n
    @ involve remove namespace bafore ::,
            and remove caller before ->, .
            and remove parameter after (\n
    """
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

def remove_given_element(element, in_list):
    """
    @ param element and list\n
    @ return new list\n
    @ involve remove given element in in_list\n
    """
    # remove element in in_list
    while element in in_list:
        in_list.remove(element)

    return in_list

def dict_from_list(in_list):
    """
    @ param list\n
    @ return dictionary\n
    @ involve transform list into dict(key:list value, value:)\n
    """
    len_list = len(in_list)
    out_dict = {}
    for i in range(len_list):
        out_dict[in_list[i]] = i

    return out_dict

def getFunctionSimilarityDic(isFromRead):
    """
    @ param flag about whether read from file\n
    @ return similarity dictionary between functions\n
    @ involve call similarity_func.getFunctionSimilarity or read from file\n
    """
    func_similarity_dic = {}
    if isFromRead:
        # initialize func_similarity_dict from file
        analyze_func = file(my_constant.FUNC_SIMILAIRTY_FILE_NAME, 'rb')
        func_records = csv.reader(analyze_func)
        for func_record in islice(func_records, 1, None):
            func_similarity_dic[(func_record[0], func_record[1])] = func_record[2]
        analyze_func.close()
    else:
        func_similarity_dic = similarity_func.getFunctionSimilarity()
    return func_similarity_dic

def remove_dict_element(dictionary, key_index):
    """
    @ param dictionary(key is two dimension) and key index\n
    @ return new dictionary\n
    @ involve remove element contains key_a or key_b specified key_index\n
    """
    key_list = dictionary.keys()
    key_a = key_list[key_index][0]
    key_b = key_list[key_index][1]
    for key in key_list:
        # if key contains key_a or key_b
        if key[0] == key_a or key[1] == key_b:
            del dictionary[key]

    return dictionary

def get_delta_of_two_set(set_a, set_b):
    """
    @ param difference of two set\n
    @ return delta_set\n
    @ involve calculate (A U B) - (A J B)[occurrence diff]\n
    """
    union_set = set_a.union(set_b)
    join_set = set_a.intersection(set_b)
    delta_set = union_set.difference(join_set)
    return delta_set

def retrieve_log_function(file_name):
    """
    @ param file name\n
    @ return log function list\n
    @ involve retrieve log function name from logging statement csv\n
    """
    log_functions = []
    log_statement = open(file_name, 'rb')
    lines = log_statement.readlines()

    for line in lines:
        log_function = line[0:line.find("@")]
        if not log_function in log_functions:
            log_functions.append(log_function)

    log_statement.close()
    return log_functions

def function_to_regrex_str(log_functions):
    """
    @ param log functions\n
    @ return regrex_string e.g. '[assert|log|debug|print|write|error]('\n
    @ involve concate log functions into regrex string\n
    """
    regrex_string = r'\W('
    for log_function in log_functions:
        regrex_string += log_function + r'|'
    regrex_string = regrex_string[:-1]
    regrex_string += r')(\s*\(.*|\s*$)'

    return regrex_string

def compute_similarity(in_vector1, in_vector2, method='braycurtis'):
    """
    @ param two number vectors(same dimension)\n
    @ return similarity\n
    @ involve compute braycurtis similarity of two vectors\n
    """
    if in_vector1 == [] or in_vector2 == []:
        return 1.0
    X = np.vstack([in_vector1, in_vector2])
    # standard distance
    distance = pdist(X, metric=method)
    similairty = 1 - distance
    return similairty

def save_file(content, file_name):
    """
    @ param file content and filename\n
    @ return nothing\n
    @ involve save file content into given file\n
    """
    write_file = open(file_name, 'wb')
    write_file.write(content)
    write_file.close()

def copy_file(old_file_name, new_file_name):
    """
    @ param old file name and new file name\n
    @ return nothing\n
    @ involve copy file from old file to new file\n
    """
    read_file = open(old_file_name, 'rb')
    content = read_file.read()
    write_file = open(new_file_name, 'wb')
    write_file.write(content)
    read_file.close()
    write_file.close()

def rebuild_joern_index(index_dir, code_dir):
    """
    @ param joernIndex parent dir(absolut), code dir to analyze\n
    @ return nothing\n
    @ involve rm old joernIndex file, and build new one. restart neo4j server\n
    """
    output = commands.getoutput('rm -r ' + index_dir)
    output = commands.getoutput('java -Xmx4g -Xms4g -jar $JOERN/bin/joern.jar ' + code_dir + ' -outdir ' + index_dir)
    output = commands.getoutput('neo4j restart')
    print output

def get_tuple_from_list(tuple_list):
    """
    @ param list of tuple\n
    @ return tuple\n
    @ involve merge list of tuple to tuple\n
    """
    tuple_tuple = ()
    for tuple_element in tuple_list:
        tuple_tuple += tuple(tuple_element)
    return tuple_tuple

def filter_file(file_name):
    """
    @ param file name\n
    @ return true if ok\n
    @ involve choose the one cpp like and not test like\n
    """
    # cpp like(ignore case)
    is_cpp = re.search(my_constant.CPP_FILE_FORMAT, file_name, re.I)
    # test like
    is_test_cpp = re.search(r'test', file_name, re.I)
    if is_cpp and not is_test_cpp:
        return True
    else:
        return False

def get_csv_record_len(records):
    """
    @ param csv records\n
    @ return length of records and list object\n
    @ involve switch iterator into list and call len()\n
    """
    records = list(records)
    return len(records), records

def get_version_number(version):
    """
    @ param file name\n
    @ return a.b.c.d -> a*1000000 + b*10000 + c*100 + d\n
    @ involve split version sub number and compute version value\n
    """
    # at most 4 pair
    pattern = r'.*-(\d*)\.(\d*)\.*(\d*)\.*(\d*)'
    info = re.match(pattern, version)
    version_number = 0
    # 100 sub version
    version_number_basis = [1000000,10000, 100, 1]
    if info:
        info = info.groups()
        for i in range(len(info)):
            if info[i] != '':
                version_number += int(info[i]) * version_number_basis[i]
    else:
        print 'error processing version dir %s' %version
    return version_number

def longest_common_sub(list_a, list_b):
    """
    @ param list of a and b\n
    @ return lenth of common substring\n
    @ involve compute the longgest common string (continuous) of two list\n
    """
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
