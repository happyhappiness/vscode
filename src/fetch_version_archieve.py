
import urllib2
import os
import re
import my_constant

def download_file(main_url, file_name):
    """
    @ param main url and file name\n
    @ return true if success\n
    @ involve download tar.gz from given url\n
    """
    # main_url = 'https://git.gnome.org/browse/gedit/snapshot/'
    # do not download file downloaded
    store_file_name = 'second/download/squid/repos/' + file_name
    if os.path.isfile(store_file_name):
        print 'already downloaded %s' %store_file_name
        return True
    file_url = main_url + file_name
    file_content = urllib2.urlopen(file_url)

    download_tar_file = open( store_file_name, 'wb')
    block_size = 8192
    while True:
        cache = file_content.read(block_size)
        if not cache:
            break
        download_tar_file.write(cache)
    download_tar_file.close()

    return True

def analyze_html(url):
    """
    @ param url\n
    @ return nothing\n
    @ involve fetch html of given url and deal with each href to download tar.gz\n
    """
    # fetch html
    response = urllib2.urlopen(url)
    html = response.read()
    html = html.split("\n")
    target_href_pattern = r'(?:href|HREF)=.*(squid-[0-9\.]*\.tar\.gz)">'
    # target_href_pattern = r'Changes for Version (\d\.\d+) \(.*\)'
    count = 0
    # check html content against git-2.*.tar.gz
    for line in html:
        is_target = re.search(target_href_pattern, line, re.I)
        if is_target:
            file_name = is_target.group(1)
            print 'now downloading %s' %(file_name)
            if download_file(url, file_name):
                count += 1
                print "have downloaded %d:%s" %(count, file_name)

"""
main function
"""
if __name__ == "__main__":
    analyze_html("http://ftp.meisei-u.ac.jp/mirror/squid/")
