#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar
{
    struct TCar              * m_Next;
    char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TCar              * m_Car;
    char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
    TEMPLOYEE                * m_Emp;
    TCAR                     * m_Car;
} TOFFICE;

typedef struct {
    TCAR *m_Next;
    char *m_Model;
    size_t index;
} TCAR_NEW;

TCAR *newCar()
{
    TCAR_NEW *new_car = (TCAR_NEW *)malloc(sizeof(TCAR_NEW));
    memset(new_car, 0, sizeof(TCAR_NEW));
    return (TCAR *)new_car;
}

TEMPLOYEE *newEmployee()
{
    TEMPLOYEE *new_employee = (TEMPLOYEE *)malloc(sizeof(TEMPLOYEE));
    memset(new_employee, 0, sizeof(TEMPLOYEE));
    return new_employee;
}

TCAR *dumpCar(TCAR *car)
{
    TCAR *new_car = newCar();
    new_car->m_Model = strdup(car->m_Model);
    return new_car;
}

TEMPLOYEE *dumpEmployee(TEMPLOYEE *employee)
{
    TEMPLOYEE *new_employee = newEmployee();
    new_employee->m_Name = strdup(employee->m_Name);
    return new_employee;
}

TOFFICE          * initOffice()
{
    TOFFICE *new_office = (TOFFICE *)malloc(sizeof(TOFFICE));
    memset(new_office, 0, sizeof(TOFFICE));
    return new_office;
}

void               addEmployee(TOFFICE         * office,
    const char      * name)
{
    TEMPLOYEE *new_employee = newEmployee();
    new_employee->m_Name = strdup(name);
    new_employee->m_Next = office->m_Emp;
    office->m_Emp = new_employee;
}
void               addCar(TOFFICE         * office,
    const char      * model)
{
    TCAR *new_car = newCar();
    new_car->m_Model = strdup(model);
    new_car->m_Next = office->m_Car;
    office->m_Car = new_car;
}
TOFFICE          * cloneOffice(TOFFICE         * office)
{
    size_t size = 0;
    for (TCAR *it = office->m_Car; it != NULL; it = it->m_Next) {
        ++size;
    }

    TCAR **cars = (TCAR **)malloc(sizeof(TCAR *) * size + 1);

    size_t index = 0;
    TCAR *car_list = NULL;
    TCAR *current_car = NULL;
    for (TCAR *it = office->m_Car; it != NULL; it = it->m_Next) {
        TCAR *new_car = dumpCar(it);
        if (car_list != NULL) {
            current_car->m_Next = new_car;
            current_car = new_car;
        }
        else {
            car_list = new_car;
            current_car = car_list;
        }

        cars[index] = new_car;
        ((TCAR_NEW *)it)->index = index++;
    }

    TEMPLOYEE *employee_list = NULL;
    TEMPLOYEE *current_employee = NULL;
    for (TEMPLOYEE *it = office->m_Emp; it != NULL; it = it->m_Next) {
        TEMPLOYEE *employee = dumpEmployee(it);
        if (employee_list != NULL) {
            current_employee->m_Next = employee;
            current_employee = employee;
        }
        else {
            employee_list = employee;
            current_employee = employee;
        }

        if (it->m_Car != NULL) {
            employee->m_Car = cars[((TCAR_NEW *)it->m_Car)->index];
        }
    }

    free(cars);

    TOFFICE *new_office = initOffice();
    new_office->m_Emp = employee_list;
    new_office->m_Car = car_list;
    return new_office;
}
void               freeOffice(TOFFICE         * office)
{
    for (TCAR *it = office->m_Car; it != NULL; ) {
        TCAR *tmp = it;
        it = it->m_Next;
        free(tmp->m_Model);
        free(tmp);
    }

    for (TEMPLOYEE *it = office->m_Emp; it != NULL;) {
        TEMPLOYEE *tmp = it;
        it = it->m_Next;
        free(tmp->m_Name);
        free(tmp);
    }

    free(office);
}

int main(int argc, char * argv[])
{
    TOFFICE * a, *b;
    char tmp[100];

    assert(sizeof(TOFFICE) == 2 * sizeof(void *));
    assert(sizeof(TEMPLOYEE) == 3 * sizeof(void *));
    assert(sizeof(TCAR) == 2 * sizeof(void *));
    a = initOffice();
    addEmployee(a, "Peter");
    addEmployee(a, "John");
    addEmployee(a, "Joe");
    addEmployee(a, "Maria");
    addCar(a, "Skoda Octavia");
    addCar(a, "VW Golf");
    a->m_Emp->m_Car = a->m_Car;
    a->m_Emp->m_Next->m_Next->m_Car = a->m_Car->m_Next;
    a->m_Emp->m_Next->m_Next->m_Next->m_Car = a->m_Car;
    assert(a->m_Emp
        && !strcmp(a->m_Emp->m_Name, "Maria")
        && a->m_Emp->m_Car == a->m_Car);
    assert(a->m_Emp->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Name, "Joe")
        && a->m_Emp->m_Next->m_Car == NULL);
    assert(a->m_Emp->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "John")
        && a->m_Emp->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert(a->m_Emp->m_Next->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
        && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car);
    assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
    assert(a->m_Car
        && !strcmp(a->m_Car->m_Model, "VW Golf"));
    assert(a->m_Car->m_Next
        && !strcmp(a->m_Car->m_Next->m_Model, "Skoda Octavia"));
    assert(a->m_Car->m_Next->m_Next == NULL);
    b = cloneOffice(a);
    strncpy(tmp, "Moe", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy(tmp, "Victoria", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy(tmp, "Peter", sizeof(tmp));
    addEmployee(a, tmp);
    strncpy(tmp, "Citroen C4", sizeof(tmp));
    addCar(a, tmp);
    b->m_Emp->m_Next->m_Next->m_Next->m_Car = b->m_Car->m_Next->m_Next;
    assert(a->m_Emp
        && !strcmp(a->m_Emp->m_Name, "Peter")
        && a->m_Emp->m_Car == NULL);
    assert(a->m_Emp->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Name, "Victoria")
        && a->m_Emp->m_Next->m_Car == NULL);
    assert(a->m_Emp->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "Moe")
        && a->m_Emp->m_Next->m_Next->m_Car == NULL);
    assert(a->m_Emp->m_Next->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Maria")
        && a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Name, "Joe")
        && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Car == NULL);
    assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "John")
        && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next->m_Next);
    assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
        && !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Peter")
        && a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
    assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    assert(a->m_Car
        && !strcmp(a->m_Car->m_Model, "Citroen C4"));
    assert(a->m_Car->m_Next
        && !strcmp(a->m_Car->m_Next->m_Model, "VW Golf"));
    assert(a->m_Car->m_Next->m_Next
        && !strcmp(a->m_Car->m_Next->m_Next->m_Model, "Skoda Octavia"));
    assert(a->m_Car->m_Next->m_Next->m_Next == NULL);
    assert(b->m_Emp
        && !strcmp(b->m_Emp->m_Name, "Maria")
        && b->m_Emp->m_Car == b->m_Car);
    assert(b->m_Emp->m_Next
        && !strcmp(b->m_Emp->m_Next->m_Name, "Joe")
        && b->m_Emp->m_Next->m_Car == NULL);
    assert(b->m_Emp->m_Next->m_Next
        && !strcmp(b->m_Emp->m_Next->m_Next->m_Name, "John")
        && b->m_Emp->m_Next->m_Next->m_Car == b->m_Car->m_Next);
    assert(b->m_Emp->m_Next->m_Next->m_Next
        && !strcmp(b->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
        && b->m_Emp->m_Next->m_Next->m_Next->m_Car == NULL);
    assert(b->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
    assert(b->m_Car
        && !strcmp(b->m_Car->m_Model, "VW Golf"));
    assert(b->m_Car->m_Next
        && !strcmp(b->m_Car->m_Next->m_Model, "Skoda Octavia"));
    assert(b->m_Car->m_Next->m_Next == NULL);
    freeOffice(a);
    freeOffice(b);
    return 0;
}