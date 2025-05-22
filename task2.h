#pragma once

typedef enum {
    FULL_TIME,      // Полная занятость
    PART_TIME,      // Частичная занятость
    CONTRACTOR,     // Внешний сотрудник
    INTERN          // Стажер
} EmploymentType;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char* position_name;
    float avg_salary;
    int count;
} PositionStats;

typedef struct {
    char* position;
    float rate;
    int monthly_salary;
    Date start_date;
    Date end_date;
} Contract;

// Узел очереди контрактов
typedef struct ContractNode {
    Contract contract;
    struct ContractNode* next;
} ContractNode;

typedef struct {
    char* full_name;
    Date birth_date;
    int personnel_number;
    EmploymentType employment_type;
    ContractNode* contracts_head; // Голова очереди контрактов
    ContractNode* contracts_tail; // Хвост очереди контрактов
    int contracts_count;         // Количество контрактов
} Worker;

// Узел очереди работников
typedef struct WorkerNode {
    Worker worker;
    struct WorkerNode* next;
} WorkerNode;

typedef struct {
    WorkerNode* workers_head;    // Голова очереди работников
    WorkerNode* workers_tail;    // Хвост очереди работников
    int workers_count;           // Количество работников
} WorkersData;

void InsertStr(char** mas);
const char* employmentTypeToString(EmploymentType type);
void printDate(const Date date);
int compareDates(Date date1, Date date2);
Date createDate();
Contract createContract();
void initContracts(Worker* worker);
void addContractToWorker(Worker* worker, Contract contract);
void freeContracts(Worker* worker);
Worker createWorker(WorkersData* data);
void printContract(Contract contract);
void printWorker(const Worker worker);
void freeWorker(Worker* worker);
void initWorkersData(WorkersData* data);
void addWorkerToData(WorkersData* data, Worker worker);
int removeWorker(WorkersData* data, int index);
void printAllWorkers(WorkersData* data);
int comparePositions(const void* a, const void* b);
PositionStats* createPositionsStats(WorkersData* data, int* stats_count);
void printPositionsStats(PositionStats* stats, int stats_count);
void positionsMenu(WorkersData* data);
void showMenu();
char* trimWhitespace(char* str);
void saveWorkersToFile(WorkersData* data, const char* filename);
void loadWorkersFromFile(WorkersData* data, const char* filename);
int isWorkerDismissed(Worker* worker, Date current_date);
void removeDismissedWorkers(WorkersData* data, Date current_date);
void removeDismissedMenu(WorkersData* data);
void freeWorkersData(WorkersData* data);
int intchar();
float floatchar();
void workerStruct(const char* argv);