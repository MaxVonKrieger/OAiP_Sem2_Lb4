#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include "task2.h"
#include "task1.h"
#include "general_f.h"

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "RU");
    int i = 0, n = 0, vibor = 0, c = 0;
    char* k = NULL;
    const char* filename = argv[1];
    while (1)
    {
        DrawMenu();
        printf_s("�������� ����� ����: ");
        vibor = intchar();

        switch (vibor)
        {
        case 1:
            printf("������� ������ � ����������� �����: ");
            InsertStr(&k);
            StackUse(k);
            break;

        case 2:
            workerStruct(filename);
            break;

        case 3:
            printf("���������� ������ ���������... \n");
            return 0;

        default:
            printf_s("�������� �����. ������� ����� �� 1 �� 3.\n");
            break;
        }
    }

    return 0;
}