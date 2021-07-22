#include <stdio.h>
#include <vector>
#include <iostream>
#include <omp.h>

bool func_proc(){ return true; }

template<typename T>
int func_hoge(const int item_num)
{
    std::vector<T> items(item_num);

    #pragma omp parallel for
    for (int ii = 0; ii < item_num; ii++) { items[ii] = (T)func_proc(); }

    int fail_cnt = 0;
    for(auto item : items) { if(!item) ++fail_cnt; }
    return fail_cnt;
}

int main()
{
    int max_num_threads = omp_get_max_threads();    // 16
    std::cout << "max_threads :" << max_num_threads << std::endl;
    omp_set_num_threads(max_num_threads);

    const int item_num = 1000;
    std::cout << "[vector type:bool] fail cnt :" << func_hoge<bool>(item_num) << std::endl;
    std::cout << "[vector type:int] fail cnt :" << func_hoge<int32_t>(item_num) << std::endl;
    std::cout << "[vector type:uint] fail cnt :" << func_hoge<uint32_t>(item_num) << std::endl;

    return 0;
}
