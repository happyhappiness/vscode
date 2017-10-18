from itertools import islice 
import csv
import json
import my_constant

"""
@ param csv file name
@ return statistic info(no.cluster, no.>1cluster, no.repeted log) 
@ involve get statistical info about cluster
"""
def statistical_cluster(csv_file_name):
    reading_file = file(csv_file_name)
    records = csv.reader(reading_file)
    statistic_dict = {}
    number_log = 0
    number_cluster = 0
    repeted_cluster = 0
    repeted_log = 0
    for record in islice(records, 1, None):
        edit_feature = json.loads(record[my_constant.ANALYZE_EDIT_FEATURE])
        number_log += 1
        # ignore empty edition
        if edit_feature == [0]:
            continue
        cluster = json.loads(record[my_constant.ANALYZE_CLUSTER])
        # if has been in dict then increment counter
        if statistic_dict.has_key(cluster):
            # first repetetion -> repeted cluster
            if statistic_dict[cluster] == 1:
                repeted_cluster += 1
                # repeted log initialize
                repeted_log += 1
            # if have repetion, increment value(mark)
            statistic_dict[cluster] += 1
            # repeted log
            repeted_log += 1
        # if new, add to dict(mark)
        else:
            statistic_dict[cluster] = 1
            number_cluster += 1

    print "log is %d, cluster is %d, repeted cluster is %d, repeted log is %d" %(number_log, number_cluster, repeted_cluster, repeted_log)


if __name__ == "__main__":
    # statistics about edition cluster
    edition_file_name = my_constant.CLUSTER_EDITION_OLD_NEW_FILE_NAME
    statistical_cluster(edition_file_name)
    # statistics about edition and feature cluster
    edition_and_feature_file_name = my_constant.CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    statistical_cluster(edition_and_feature_file_name)
