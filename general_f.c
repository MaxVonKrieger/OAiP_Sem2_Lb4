#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int strDlin(const char* str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

void centrirovText(const char* text)
{
    int consoleWidth = 80;
    int textLength = strDlin(text);
    int padding = (consoleWidth - textLength) / 2;
    for (int i = 0; i < padding; i++)
    {
        printf_s(" ");
    }
    printf("%s", text);
    for (int i = 0; i < padding; i++)
    {
        printf_s(" ");
    }
    printf_s("\n");
}

void DrawMenu()
{
    centrirovText(" ____________________________________________________ ");
    centrirovText("|                                                    |");
    centrirovText("|                        ����                        |");
    centrirovText("|____________________________________________________|");
    centrirovText("|                                                    |");
    centrirovText("| 1. ����� ����� ����� ����� � ��������� ������      |");
    centrirovText("| 2. ��������� ��������                              |");
    centrirovText("| 3. ����� �� ���������                              |");
    centrirovText("|____________________________________________________|");
}

void DrawSubMenu()
{
    centrirovText(" _____________________________ ");
    centrirovText("|                             |");
    centrirovText("|         ������ �����        |");
    centrirovText("|_____________________________|");
    centrirovText("|                             |");
    centrirovText("| 1. ��������� ����           |");
    centrirovText("| 2. ������ ����              |");
    centrirovText("|_____________________________|");
}

float floatchar() {
    char k;
    int i = 0;
    int has_decimal_point = 0;  // ���� ������� �����/�������
    int decimal_places = 0;     // ���������� ���� ����� �����
    int is_negative = 0;        // ���� �������������� �����
    float result = 0.0f;        // ���������
    float decimal_multiplier = 1.0f; // ��������� ��� ������� �����

    // ������ ������ (���� ��� �����)
    k = _getch();

    // ��������� �����
    if (k == '+' || k == '-') {
        printf("%c", k);
        is_negative = (k == '-');
        k = _getch();  // ��������� ��������� ������
    }
    else {
        printf("+");  // ���� ���� �� �����, ������������� '+'
    }

    // �������� ���� �����
    while (1) {
        // �����
        if (k >= '0' && k <= '9') {
            printf("%c", k);
            if (!has_decimal_point) {
                result = result * 10 + (k - '0');
            }
            else {
                decimal_places++;
                decimal_multiplier *= 0.1f;
                result += (k - '0') * decimal_multiplier;
            }
        }
        // ����� ��� ������� (������ ����)
        else if ((k == '.' || k == ',') && !has_decimal_point) {
            printf(".");
            has_decimal_point = 1;
        }
        // Enter (���������� �����, ���� ���� ���� �� ���� �����)
        else if (k == '\r' && i >= 1) {
            printf("\n");
            break;
        }
        // Backspace (�������� ���������� �������)
        else if (k == '\b' && i >= 1) {
            printf("\b \b");
            if (has_decimal_point && decimal_places > 0) {
                decimal_places--;
                decimal_multiplier /= 0.1f;
                // ��������� ������� ����� ����� � ��������� ���������
                // (��� ������ ������� �����, ������� ����� ���������� Backspace)
            }
            else {
                result = (int)(result / 10);  // ������ �������� ��������� �����
            }
            i--;
            continue;
        }

        i++;
        k = _getch();
    }

    return is_negative ? -result : result;
}

int intchar()
{
    char k;
    int l = 0, i = 0;
    char* mas = (char*)malloc(1);
    if (mas == NULL)
    {
        printf("������ ��������� ������ ��� �����\n");
        return 1;
    }

    while (1) {
        k = _getch();
        if (k >= '0' && k <= '9')
        {
            printf("%c", k);
            mas[i] = k;
            i++;
            char* temp = (char*)realloc(mas, i + 1);
            if (temp == NULL)
            {
                printf("������ ����������������� ������ ��� �����\n");
                free(mas);
                return 1;
            }
            mas = temp;
            mas[i] = '\0';
        }
        else if (k == '\r' && i != 0)
        {
            printf("\n");
            break;
        }
        else if (k == '\b')
        {
            if (i > 0)
            {
                i--;
                mas[i] = '\0';
                printf("\b \b");
            }
        }
    }

    for (int j = 0; j < i; j++)
    {
        l = l * 10 + (mas[j] - '0');
    }
    free(mas);
    return l;
}