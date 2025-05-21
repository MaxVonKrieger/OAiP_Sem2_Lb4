#define _CRT_SECURE_NO_WARNINGS
#include "task2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


void InsertStr(char** mas) {
    char a;
    int i = 0;
    *mas = (char*)malloc(1);
    if (*mas == NULL) {
        printf("������ ��������� ������\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        a = _getch();
        if (a == '\r') break;
        if (a == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
                char* temp = (char*)realloc(*mas, i + 1);
                if (temp == NULL) {
                    printf("������ ����������������� ������\n");
                    exit(EXIT_FAILURE);
                }
                *mas = temp;
            }
            continue;
        }
        printf("%c", a);
        char* temp = (char*)realloc(*mas, i + 2);
        if (temp == NULL) {
            printf("������ ����������������� ������\n");
            exit(EXIT_FAILURE);
        }
        *mas = temp;
        (*mas)[i] = a;
        i++;
    }
    (*mas)[i] = '\0';
}

void printDate(const Date date) {
    printf("[����: %02d.%02d.%04d]", date.day, date.month, date.year);
}

const char* employmentTypeToString(EmploymentType type) {
    switch (type) {
    case FULL_TIME: return "������ ���������";
    case PART_TIME: return "��������� ���������";
    case CONTRACTOR: return "������� ���������";
    case INTERN: return "������";
    default: return "����������� ���";
    }
}

int compareDates(Date date1, Date date2) {
    if (date1.year > date2.year) return 1;
    if (date1.year < date2.year) return -1;
    if (date1.month > date2.month) return 1;
    if (date1.month < date2.month) return -1;
    if (date1.day > date2.day) return 1;
    if (date1.day < date2.day) return -1;
    return 0;
}

Date createDate() {
    Date result;
    do {
        printf("\n������� ���� (�� 01 �� 31): ");
        result.day = intchar();
    } while (result.day < 1 || result.day > 31);

    do {
        printf("\n������� ����� (�� 01 �� 12): ");
        result.month = intchar();
    } while (result.month < 1 || result.month > 12);

    do {
        printf("\n������� ���(____): ");
        result.year = intchar();
    } while (result.year < 1900 || result.year > 2100);

    printf("\n");
    return result;
}

Contract createContract() {
    Contract result;
    result.position = NULL;

    printf("\n������� ���������: ");
    InsertStr(&result.position);

    do {
        printf("\n������� ������ (0.1-10.0): ");
        result.rate = floatchar();
    } while (result.rate < 0.1f || result.rate > 10.0f);

    do {
        printf("\n������� ����������� �������� (> 0): ");
        result.monthly_salary = intchar();
    } while (result.monthly_salary <= 0);

    printf("\n���� ������ ���������:");
    result.start_date = createDate();

    do {
        printf("\n���� ��������� ���������:");
        result.end_date = createDate();
        if (compareDates(result.end_date, result.start_date) < 0) {
            printf("���� ��������� ������ ���� ����� ���� ������!\n");
        }
    } while (compareDates(result.end_date, result.start_date) < 0);

    return result;
}

void initContracts(Worker* worker) {
    worker->contracts_head = NULL;
    worker->contracts_tail = NULL;
    worker->contracts_count = 0;
}

void addContractToWorker(Worker* worker, Contract contract) {
    ContractNode* new_node = (ContractNode*)malloc(sizeof(ContractNode));
    if (new_node == NULL) {
        printf("������ ��������� ������ ��� ������ ���������\n");
        exit(EXIT_FAILURE);
    }

    new_node->contract = contract;
    new_node->next = NULL;

    if (worker->contracts_head == NULL) {
        worker->contracts_head = new_node;
        worker->contracts_tail = new_node;
    }
    else {
        worker->contracts_tail->next = new_node;
        worker->contracts_tail = new_node;
    }

    worker->contracts_count++;
}

void freeContracts(Worker* worker) {
    ContractNode* current = worker->contracts_head;
    while (current != NULL) {
        ContractNode* next = current->next;
        if (current->contract.position != NULL) {
            free(current->contract.position);
        }
        free(current);
        current = next;
    }
    worker->contracts_head = NULL;
    worker->contracts_tail = NULL;
    worker->contracts_count = 0;
}

Worker createWorker(WorkersData* data) {
    Worker result;
    result.full_name = NULL;
    initContracts(&result);

    printf("\n������� ��� ���������: ");
    InsertStr(&result.full_name);

    printf("\n���� �������� ���������:\n");
    result.birth_date = createDate();

    // ���� ���� ���������
    printf("\n�������� ��� ���������:\n");
    printf("1. ������ ���������\n");
    printf("2. ��������� ���������\n");
    printf("3. ������� ���������\n");
    printf("4. ������\n");
    printf("�����: ");

    int type_choice;
    do {
        type_choice = intchar();
        if (type_choice < 1 || type_choice > 4) {
            printf("�������� �����! ������� ����� �� 1 �� 4: ");
        }
    } while (type_choice < 1 || type_choice > 4);

    result.employment_type = (EmploymentType)(type_choice - 1);

    // ���� ���������� ������ � ��������� �� ������������
    int is_unique;
    do {
        is_unique = 1;
        printf("\n������� ��������� ����� (���������� ����� > 0): ");
        result.personnel_number = intchar();

        if (result.personnel_number <= 0) {
            printf("��������� ����� ������ ���� ������������� ������!\n");
            continue;
        }

        WorkerNode* current = data->workers_head;
        while (current != NULL) {
            if (current->worker.personnel_number == result.personnel_number) {
                printf("������: �������� � ��������� ������� %d ��� ����������!\n",
                    result.personnel_number);
                is_unique = 0;
                break;
            }
            current = current->next;
        }

        if (!is_unique) {
            printf("����������, ������� ������ ��������� �����.\n");
        }
    } while (result.personnel_number <= 0 || !is_unique);

    // ���� ����������
    char add_more;
    do {
        printf("\n���� ������ ��������� #%d:\n", result.contracts_count + 1);
        Contract new_contract = createContract();
        addContractToWorker(&result, new_contract);

        if (result.contracts_count < 10) {
            printf("\n�������� ��� ���� �������� ��� ����� ���������? (y/n): ");
            add_more = _getch();
            printf("%c\n", add_more);
        }
        else {
            printf("\n���������� ������������ ���������� ���������� (10)\n");
            add_more = 'n';
        }
    } while ((add_more == 'y' || add_more == 'Y') && result.contracts_count < 10);

    return result;
}

void printContract(Contract contract) {
    printf("���������: %s\n", contract.position);
    printf("������: %.2f\n", contract.rate);
    printf("��������: %d ���./���.\n", contract.monthly_salary);
    printf("���� ������: ");
    printDate(contract.start_date);
    printf("\n");
    printf("���� ���������: ");
    printDate(contract.end_date);
    printf("\n");
}

void printWorker(const Worker worker) {
    printf("\n=== ���������� � ��������� ===\n");
    printf("���: %s\n", worker.full_name);
    printf("���� ��������: ");
    printDate(worker.birth_date);
    printf("\n");
    printf("��������� �����: %d\n", worker.personnel_number);
    printf("��� ���������: %s\n", employmentTypeToString(worker.employment_type));

    printf("\n--- ������ ���������� (%d) ---\n", worker.contracts_count);
    ContractNode* current = worker.contracts_head;
    int i = 1;
    while (current != NULL) {
        printf("\n�������� #%d:\n", i++);
        printContract(current->contract);
        current = current->next;
    }
    printf("===========================\n");
}

void freeWorker(Worker* worker) {
    if (worker == NULL) return;

    if (worker->full_name != NULL) {
        free(worker->full_name);
        worker->full_name = NULL;
    }

    freeContracts(worker);
}

void initWorkersData(WorkersData* data) {
    data->workers_head = NULL;
    data->workers_tail = NULL;
    data->workers_count = 0;
}

void addWorkerToData(WorkersData* data, Worker worker) {
    WorkerNode* new_node = (WorkerNode*)malloc(sizeof(WorkerNode));
    if (new_node == NULL) {
        printf("������ ��������� ������ ��� ������ ���������\n");
        exit(EXIT_FAILURE);
    }

    new_node->worker = worker;
    new_node->next = NULL;

    if (data->workers_head == NULL) {
        data->workers_head = new_node;
        data->workers_tail = new_node;
    }
    else {
        data->workers_tail->next = new_node;
        data->workers_tail = new_node;
    }

    data->workers_count++;
}

int removeWorker(WorkersData* data, int index) {
    if (index < 0 || index >= data->workers_count) {
        return 0;
    }

    WorkerNode* prev = NULL;
    WorkerNode* current = data->workers_head;

    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        data->workers_head = current->next;
    }
    else {
        prev->next = current->next;
    }

    if (current == data->workers_tail) {
        data->workers_tail = prev;
    }

    freeWorker(&current->worker);
    free(current);
    data->workers_count--;

    return 1;
}

void printAllWorkers(WorkersData* data) {
    if (data->workers_count == 0) {
        printf("\n=== ��� ������ � ���������� ===\n");
        return;
    }

    printf("\n=== ������ ���������� (%d) ===\n", data->workers_count);
    WorkerNode* current = data->workers_head;
    int i = 1;

    while (current != NULL) {
        printf("\n[�������� #%d]\n", i++);
        printWorker(current->worker);
        current = current->next;
    }

    printf("\n=== ����� ������ ===\n");
}

int comparePositions(const void* a, const void* b) {
    const PositionStats* pa = (const PositionStats*)a;
    const PositionStats* pb = (const PositionStats*)b;

    if (pa->avg_salary > pb->avg_salary) return -1;
    if (pa->avg_salary < pb->avg_salary) return 1;
    return 0;
}

PositionStats* createPositionsStats(WorkersData* data, int* stats_count) {
    *stats_count = 0;
    if (data->workers_count == 0) {
        return NULL;
    }

    PositionStats* stats = NULL;
    int stats_capacity = 10;
    stats = (PositionStats*)malloc(stats_capacity * sizeof(PositionStats));
    if (stats == NULL) {
        printf("������ ��������� ������!\n");
        return NULL;
    }

    WorkerNode* current_worker = data->workers_head;
    while (current_worker != NULL) {
        ContractNode* current_contract = current_worker->worker.contracts_head;
        while (current_contract != NULL) {
            char* current_pos = current_contract->contract.position;
            int found = 0;

            for (int j = 0; j < *stats_count; j++) {
                if (strcmp(stats[j].position_name, current_pos) == 0) {
                    stats[j].avg_salary = (stats[j].avg_salary * stats[j].count +
                        current_contract->contract.monthly_salary) /
                        (stats[j].count + 1);
                    stats[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (*stats_count >= stats_capacity) {
                    stats_capacity *= 2;
                    PositionStats* temp = realloc(stats, stats_capacity * sizeof(PositionStats));
                    if (temp == NULL) {
                        printf("������ ����������������� ������!\n");
                        for (int m = 0; m < *stats_count; m++) {
                            free(stats[m].position_name);
                        }
                        free(stats);
                        return NULL;
                    }
                    stats = temp;
                }

                stats[*stats_count].position_name = _strdup(current_pos);
                if (stats[*stats_count].position_name == NULL) {
                    printf("������ ��������� ������ ��� �������� ���������!\n");
                    for (int m = 0; m < *stats_count; m++) {
                        free(stats[m].position_name);
                    }
                    free(stats);
                    return NULL;
                }
                stats[*stats_count].avg_salary = current_contract->contract.monthly_salary;
                stats[*stats_count].count = 1;
                (*stats_count)++;
            }

            current_contract = current_contract->next;
        }

        current_worker = current_worker->next;
    }

    qsort(stats, *stats_count, sizeof(PositionStats), comparePositions);
    return stats;
}

void printPositionsStats(PositionStats* stats, int stats_count) {
    if (stats == NULL || stats_count == 0) {
        printf("��� ������ ��� �����������!\n");
        return;
    }

    printf("\n=== ��� ��������� (%d) ===\n", stats_count);
    printf("%-30s %-15s %-10s\n", "���������", "������� ��������", "���-��");
    printf("------------------------------------------------\n");

    for (int i = 0; i < stats_count; i++) {
        printf("%-30s %-15.2f %-10d\n",
            stats[i].position_name,
            stats[i].avg_salary,
            stats[i].count);
    }
    printf("================================================\n");
}

void positionsMenu(WorkersData* data) {
    if (data->workers_count == 0) {
        printf("��� ������ � ����������!\n");
        return;
    }

    int stats_count = 0;
    PositionStats* stats = createPositionsStats(data, &stats_count);
    if (stats != NULL) {
        printPositionsStats(stats, stats_count);

        for (int i = 0; i < stats_count; i++) {
            free(stats[i].position_name);
        }
        free(stats);
    }
}

void showMenu() {
    printf("\n1. �������� ���������\n");
    printf("2. ������� ���������\n");
    printf("3. �������� ���� ����������\n");
    printf("4. ��� ���������� �� ��������\n");
    printf("5. ������� ��������� ����������\n");
    printf("6. ������ ����������� �� ���� ���������\n");  // ����� ����� ����
    printf("7. ��������� ������ � ����\n");
    printf("8. ��������� ������ �� �����\n");
    printf("0. �����\n");
    printf("�����: ");
}

char* trimWhitespace(char* str) {
    if (str == NULL) return NULL;

    char* end;

    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    return str;
}

void saveWorkersToFile(WorkersData* data, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������!\n");
        return;
    }

    WorkerNode* current = data->workers_head;
    while (current != NULL) {
        Worker* worker = &current->worker;

        fprintf(file, "%d | %s | %d | %d | %d | %d | %d",
            worker->contracts_count,
            worker->full_name,
            worker->birth_date.day, worker->birth_date.month, worker->birth_date.year,
            worker->personnel_number,
            worker->employment_type);

        ContractNode* contract_node = worker->contracts_head;
        while (contract_node != NULL) {
            Contract* contract = &contract_node->contract;
            fprintf(file, " | %s | %.2f | %d | %d | %d | %d | %d | %d | %d",
                contract->position,
                contract->rate,
                contract->monthly_salary,
                contract->start_date.day, contract->start_date.month, contract->start_date.year,
                contract->end_date.day, contract->end_date.month, contract->end_date.year);

            contract_node = contract_node->next;
        }
        fprintf(file, "\n");

        current = current->next;
    }

    fclose(file);
    printf("������ ������� ��������� � ���� %s\n", filename);
}

void loadWorkersFromFile(WorkersData* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("���� %s �� ������ ��� �� ����� ���� ������!\n", filename);
        return;
    }

    freeWorkersData(data);
    initWorkersData(data);

    char line[4096];
    while (fgets(line, sizeof(line), file)) {
        Worker new_worker;
        new_worker.full_name = NULL;
        initContracts(&new_worker);

        char* token = strtok(line, "|");
        if (token == NULL) continue;
        int contracts_count = atoi(trimWhitespace(token));

        token = strtok(NULL, "|");
        new_worker.full_name = (char*)malloc(strlen(trimWhitespace(token)) + 1);
        strcpy(new_worker.full_name, trimWhitespace(token));

        token = strtok(NULL, "|"); new_worker.birth_date.day = atoi(trimWhitespace(token));
        token = strtok(NULL, "|"); new_worker.birth_date.month = atoi(trimWhitespace(token));
        token = strtok(NULL, "|"); new_worker.birth_date.year = atoi(trimWhitespace(token));
        token = strtok(NULL, "|"); new_worker.personnel_number = atoi(trimWhitespace(token));
        token = strtok(NULL, "|"); new_worker.employment_type = (EmploymentType)atoi(trimWhitespace(token));

        for (int i = 0; i < contracts_count; i++) {
            Contract contract;
            contract.position = NULL;

            token = strtok(NULL, "|");
            if (token == NULL) break;
            contract.position = (char*)malloc(strlen(trimWhitespace(token)) + 1);
            strcpy(contract.position, trimWhitespace(token));

            token = strtok(NULL, "|"); if (token == NULL) break; contract.rate = atof(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.monthly_salary = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.start_date.day = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.start_date.month = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.start_date.year = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.end_date.day = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.end_date.month = atoi(trimWhitespace(token));
            token = strtok(NULL, "|"); if (token == NULL) break; contract.end_date.year = atoi(trimWhitespace(token));

            addContractToWorker(&new_worker, contract);
        }

        addWorkerToData(data, new_worker);
    }

    fclose(file);
    printf("��������� %d ���������� �� �����.\n", data->workers_count);
}

int isWorkerDismissed(Worker* worker, Date current_date) {
    if (worker->contracts_count == 0) {
        return 1;
    }

    ContractNode* current = worker->contracts_head;
    while (current != NULL) {
        if (compareDates(current_date, current->contract.start_date) >= 0 &&
            compareDates(current_date, current->contract.end_date) <= 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void removeDismissedWorkers(WorkersData* data, Date current_date) {
    if (data->workers_count == 0) {
        printf("��� ���������� ��� ��������!\n");
        return;
    }

    int removed_count = 0;
    int i = 0;
    WorkerNode* current = data->workers_head;
    WorkerNode* prev = NULL;

    while (current != NULL) {
        WorkerNode* next = current->next;

        if (isWorkerDismissed(&current->worker, current_date)) {
            printf("������� ���������� ���������: %s\n", current->worker.full_name);

            if (prev == NULL) {
                data->workers_head = next;
            }
            else {
                prev->next = next;
            }

            if (current == data->workers_tail) {
                data->workers_tail = prev;
            }

            freeWorker(&current->worker);
            free(current);
            data->workers_count--;
            removed_count++;
        }
        else {
            prev = current;
        }

        current = next;
    }

    if (removed_count == 0) {
        printf("��� ��������� ���������� �� ��������� ����.\n");
    }
    else {
        printf("������� %d ��������� ����������. �������� %d ����������.\n",
            removed_count, data->workers_count);
    }
}

void removeDismissedMenu(WorkersData* data) {
    if (data->workers_count == 0) {
        printf("��� ���������� ��� ��������!\n");
        return;
    }

    printf("\n=== �������� ��������� ���������� ===\n");
    printf("������� ������� ���� ��� ��������:\n");
    Date current_date = createDate();

    removeDismissedWorkers(data, current_date);
}

void freeWorkersData(WorkersData* data) {
    WorkerNode* current = data->workers_head;
    while (current != NULL) {
        WorkerNode* next = current->next;
        freeWorker(&current->worker);
        free(current);
        current = next;
    }

    data->workers_head = NULL;
    data->workers_tail = NULL;
    data->workers_count = 0;
}

void printWorkersByEmploymentType(WorkersData* data) {
    if (data->workers_count == 0) {
        printf("\n=== ��� ������ � ���������� ===\n");
        return;
    }

    printf("\n=== ����� ���� ��������� ===\n");
    printf("1. ������ ���������\n");
    printf("2. ��������� ���������\n");
    printf("3. ������� ���������\n");
    printf("4. ������\n");
    printf("�������� ��� ��������� (1-4): ");

    int type_choice;
    do {
        type_choice = intchar();
        if (type_choice < 1 || type_choice > 4) {
            printf("�������� �����! ������� ����� �� 1 �� 4: ");
        }
    } while (type_choice < 1 || type_choice > 4);

    EmploymentType selected_type = (EmploymentType)(type_choice - 1);
    const char* type_name = employmentTypeToString(selected_type);

    printf("\n=== ������ ����������� � ����� ���������: %s ===\n", type_name);

    WorkerNode* current = data->workers_head;
    int count = 0;

    while (current != NULL) {
        if (current->worker.employment_type == selected_type) {
            printf("\n[��������� #%d]\n", ++count);
            printf("���: %s\n", current->worker.full_name);
            printf("��������� �����: %d\n", current->worker.personnel_number);
            printf("���������� ����������: %d\n", current->worker.contracts_count);
        }
        current = current->next;
    }

    if (count == 0) {
        printf("\n��� ����������� � ��������� ����� ���������.\n");
    }
    else {
        printf("\n=== ������� �����������: %d ===\n", count);
    }
}

void workerStruct(const char* filename) {
    int exit_submenu = 0;
    WorkersData workers_data;
    initWorkersData(&workers_data);
    do {
        showMenu();
        int answer = intchar();
        switch (answer) {
        case 1:
        {
            Worker new_worker = createWorker(&workers_data);
            addWorkerToData(&workers_data, new_worker);
            printf("\n�������� %s ������� ��������! ��������� �����: %d, ����������: %d\n",
                new_worker.full_name, new_worker.personnel_number, new_worker.contracts_count);
        }
        break;
        case 2:
            if (workers_data.workers_count == 0) {
                printf("\n������ ���������� ����!\n");
                break;
            }

            printAllWorkers(&workers_data);

            int index;
            do {
                printf("\n������� ������ ��������� ��� �������� (1-%d) ��� 0 ��� ������: ",
                    workers_data.workers_count);
                index = intchar();

                if (index == 0) {
                    printf("�������� ��������.\n");
                    break;
                }

                if (index < 0 || index > workers_data.workers_count) {
                    printf("������: �������� ������! ���������� �����.\n");
                }
                else {
                    WorkerNode* node = workers_data.workers_head;
                    for (int i = 1; i < index; i++) {
                        node = node->next;
                    }

                    printf("\n�� ������������� ������ ������� ��������� %s? (1 - ��, 0 - ���): ",
                        node->worker.full_name);

                    int confirm;
                    do {
                        confirm = intchar();
                        if (confirm != 0 && confirm != 1) {
                            printf("������� 1 ��� ������������� ��� 0 ��� ������: ");
                        }
                    } while (confirm != 0 && confirm != 1);

                    if (confirm == 1) {
                        if (removeWorker(&workers_data, index - 1)) {
                            printf("\n�������� ������� ������!\n");
                            printf("�������� ����������: %d\n", workers_data.workers_count);
                        }
                        else {
                            printf("\n������ ��� �������� ���������!\n");
                        }
                    }
                    else {
                        printf("�������� ��������.\n");
                    }
                    break;
                }
            } while (1);
            break;
        case 3:
            printAllWorkers(&workers_data);
            break;
        case 4:
            positionsMenu(&workers_data);
            break;
        case 5:
            removeDismissedMenu(&workers_data);
            break;
        case 6:
            printWorkersByEmploymentType(&workers_data);  // ����� ����� ����
            break;
        case 7:
            saveWorkersToFile(&workers_data, filename);
            break;
        case 8:
            loadWorkersFromFile(&workers_data, filename);
            break;
        case 0:
            printf("����� �� ���������...\n");
            exit_submenu = 1;
            break;
        default:
            printf("�������� �����!\n");
            break;
        }

    } while (!exit_submenu);

    freeWorkersData(&workers_data);
}