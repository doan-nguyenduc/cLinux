import configparser
import os

array_filename = []
nmbr_line_equal = 0
search_dir = ""

def compare_two_files(file1, file2):
    array1 = []
    array2 = []
    with open(search_dir+file1) as f:
        for line in f:
            array1.append(line.strip())

    with open(search_dir+file2) as f:
        for line in f:
            array2.append(line.strip())


    sCount = 0
    sPos = 0
    for i in range(len(array1)):
        if i < sPos:
            continue
        if i + nmbr_line_equal > len(array1):
            break
        sPos = i
        print("i = ", i)
        for j in range(len(array2)):
            if j + nmbr_line_equal > len(array2):
                break
            print ("j = ",j)
            if array1[i] == array2[j]:
                print ("Here",i,j)
                sCount = 0
                for k in range(1,nmbr_line_equal):
                    print(array1[i+k],array2[j+k])
                    if array1[i+k] == array2[j+k]:
                        sCount = sCount + 1
                        print ("sCount = ",sCount)
                        print ("k = ",k)
                if sCount == nmbr_line_equal - 1:
                    print ("FOUND")
                    sPos += nmbr_line_equal
                    sCount = 0
                    print ("i = ",i)



def search_common_source_under_dir():
    #Loop all the file name in array_filename then compare between two files to find common source

    nmbr_of_file = len(array_filename)
    print (array_filename)
    print("number of file found is:",nmbr_of_file )
    for i in range(nmbr_of_file):
        for j in range(i+1,nmbr_of_file):
            print(array_filename[i],array_filename[j])
            compare_two_files(array_filename[i], array_filename[j])


def read_config_file():
    config = configparser.RawConfigParser()
    config.read('search.cfg')
    config_dict = dict(config.items('SEARCH_CONFIG'))
    global nmbr_line_equal
    nmbr_line_equal = int(config_dict['number_of_line_equal'])
    global search_dir
    search_dir = config_dict['search_directory']
    file_type = config_dict['file_type']
    #search all the existing file under search_dir and store it to array_filename
    for file in os.listdir(search_dir):
        if file.endswith(file_type):
            array_filename.append(file.strip())



read_config_file()
search_common_source_under_dir()

