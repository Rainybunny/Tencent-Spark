from libcpp.vector cimport vector
from libcpp.string cimport string
from libc.stdlib cimport malloc, free

cdef extern from "libmapping.so":
    vector[string] mapping_wrapper "mapping_wrapper" (const vector[string]& cf)

def py_mapping(list input_list):
    # 将 Python list 转换为 C++ vector
    cdef vector[string] c_input = new_vector_from_list(input_list)
    cdef vector[string] c_output

    # 调用 C++ 函数
    c_output = mapping_wrapper(c_input)

    # 将结果转换回 Python list
    result_list = list_from_vector(c_output)

    # 清理 C++ vector 内存
    del_vector(c_input)
    del_vector(c_output)

    return result_list


cdef vector[string] new_vector_from_list(list input_list):
    cdef vector[string] v
    for item in input_list:
        v.push_back(item)
    return v

cdef list list_from_vector(vector[string] v):
    cdef list result = []
    for item in v:
        result.append(item)
    return result

cdef void del_vector(vector[string] v):
    for item in v:
        v.clear()
        v.shrink_to_fit()