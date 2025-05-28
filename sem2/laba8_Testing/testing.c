#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

int* Filllne(int begin, int size, int* massive);
int* FillDie(int begin, int size, int* massive);
int* FillRand(int size, int* massive);
int Runnumber(int size, int* massive);
int CheckSum(int size, int* massive);
void Printer(int* massive);

static void print_test_header(const char* name) {
    printf("\n\033[1;34m[ TEST ]\033[0m \033[1;36m%s\033[0m\n", name);
}

static void print_test_result(int result) {
    if (result) {
        printf("\033[1;32m[  OK  ]\033[0m\n");
    } else {
        printf("\033[1;31m[ FAIL ]\033[0m\n");
    }
}

static void test_Filllne(void** state) {
    print_test_header("Filllne: создание возрастающего массива");
    int arr[5];
    Filllne(10, 5, arr);

    assert_int_equal(arr[0], 10);
    assert_int_equal(arr[1], 13);
    assert_int_equal(arr[2], 12);
    assert_int_equal(arr[3], 13);
    assert_int_equal(arr[4], 14);
    print_test_result(1);
}

static void test_FillDie(void** state) {
    print_test_header("FillDie: создание убывающего массива");
    int arr[5];
    FillDie(10, 5, arr);

    assert_int_equal(arr[0], 10);
    assert_int_equal(arr[1], 9);
    assert_int_equal(arr[2], 8);
    assert_int_equal(arr[3], 7);
    assert_int_equal(arr[4], 6);
    print_test_result(1);
}

static void test_Runnumber(void** state) {
    print_test_header("Runnumber: подсчет серий в массиве");
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {5, 4, 3, 2, 1};
    int arr3[5] = {1, 3, 2, 4, 0};

    assert_int_equal(Runnumber(5, arr1), 1);
    assert_int_equal(Runnumber(5, arr2), 5);
    assert_int_equal(Runnumber(5, arr3), 3);
    print_test_result(1);
}
