/*
--------------------------------------------------
Project: a4q1
File:    mysort.h
Author:  Antoine Youssef
Version: 2025-01-09
--------------------------------------------------
*/

#ifndef MYSORT_H
#define MYSORT_H 

// your code document
void select_sort(void *a[], int left, int right);

// your code document
void quick_sort(void *a[], int left, int right);

// your code document
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) );

#endif