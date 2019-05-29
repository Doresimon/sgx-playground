/*
 * Copyright (C) 2011-2018 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include "../App.h"
#include "Enclave_u.h"


void untrusted_cal_avg_darr(int len, int *arr, int *out);

/* ecall_libc_functions:
 *   Invokes standard C functions.
 */
void ecall_play_functions(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    // 1

    printf("\n\n########## START ############\n\n");
    printf("明文输入数组, 明文返回结果\n");
    printf("- 定长数组\n");
    printf("arr[4] = {6, 6, 6, 6}\n");

    int arr[4] = {6, 6, 6, 6};
    int avg = 0;
    ret = ecall_cal_avg(global_eid, arr, &avg);
    if (ret != SGX_SUCCESS)
        abort();


    printf("avg = %d \n", avg);
    printf("\n\n########## DONE #############\n\n");


    // 2

    printf("\n\n########## START ############\n\n");
    printf("明文输入数组, 明文返回结果\n");
    printf("- 不定长数组\n");
    printf("- 必须在.edl文件中声明出输入的数组的长度, 否则无法拷贝进入enclave\n");
    printf("{5, 5, 5, 5, 5, 5}\n");

    int len = 6;
    int *darr = (int *)malloc(sizeof(int) * len);
    
    for(int i = 0; i < len; i++){
        darr[i] = 5;
    }

    // untrusted_cal_avg_darr(len, darr, &avg); // ok 
    ret = ecall_cal_avg_darr(global_eid, 6, darr, &avg);
    if (ret != SGX_SUCCESS)
        abort();


    printf("avg = %d \n", avg);
    printf("\n\n########## DONE #############\n\n");
}


/* untrusted_cal_avg_darr
 *   Calculate average of an int array, 
 */
void untrusted_cal_avg_darr(int len, int *arr, int *out)
{
    int avg = 0;
    for (int i = 0; i < len; i++)
    {
        avg += arr[i];
    }
    avg = avg / len;
    *out = avg;
}